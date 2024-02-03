
#include <logger.h>
#include <logger-sink-stdstream.h>
#include <async.h>
#include <cli.h>

class Client {

public:
  Client( const std::string& ip, const std::string& port );
  void handleRead( size_t size, const uint8_t*data );
  void handleError();
  void sendPacket();
  
private:
  pubsub::Subscriber m_subscriber;
  std::shared_ptr<async::ReactorIf> m_reactor;
  std::shared_ptr<async::SocketIf> m_client;
  size_t m_count = 0;
};

Client::Client( const std::string& ip, const std::string& port ) {
  m_reactor = std::make_shared<async::Reactor>();
  m_client = async::SocketFactory( ip, std::stoi( port ) ).build();
  m_client->p_read.subscribe( &m_subscriber, this, &Client::handleRead );
  m_client->p_error.subscribe( &m_subscriber, this, &Client::handleError );
  m_reactor->inject( m_client );
  sendPacket();
  m_reactor->start();
}

void Client::handleRead( size_t size, const uint8_t*data ) {
  logger::info( "async.example.client" ) << "Received " << size << " bytes, with count " << static_cast<int>( data[0] );
  if ( m_count++ > 9u ) {
    m_reactor->stop();
  }
  else {
    sendPacket();
  }
}
  
void Client::handleError() {
  m_reactor->finally( [this]() { this->m_client.reset(); } );
}

void Client::sendPacket() {
  const auto count = static_cast<uint8_t>( m_count );
  std::vector<uint8_t> data = { count, count, count };
  logger::info( "async.example.client" ) << "Sending " << data.size() << " bytes";
  m_client->write( data.size(), data.data() );
}
  
int main( int argc, char **argv ) {

  std::string ip = "127.0.0.1";
  std::string port = "7575";
  {
    cli::Parser parser;
    parser.addOption( ip, "a", "address" );
    parser.addOption( port, "p", "port" );
    parser.parseArgs( argc, argv );
  }

  logger::Logger::get().addSink( std::shared_ptr<logger::SinkIf>( new logger::StdStreamSink() ) );
  logger::Logger::get().setLevel( logger::lDEBUG );
  {
    Client client( ip, port );
  }
  logger::Logger::get().clearSinks();
}
