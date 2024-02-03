
#include <logger.h>
#include <logger-sink-stdstream.h>
#include <async.h>
#include <pubsub.h>
#include <cli.h>

class Server {

public:
  Server( const std::string& ip, const std::string& port );
  void addClient( std::shared_ptr<async::SocketIf> socket );
  void exitServer();
  
private:
  pubsub::Subscriber m_subscriber;
  std::shared_ptr<async::ReactorIf> m_reactor;
  std::shared_ptr<async::ListenerIf> m_listener;
  std::shared_ptr<async::SocketIf> m_client;
};

Server::Server( const std::string& ip, const std::string& port ) {
  m_reactor = std::make_shared<async::Reactor>();
  m_listener = async::ListenerFactory( ip, std::stoi( port ) ).build();
  m_listener->p_read.subscribe( &m_subscriber, this, &Server::addClient );
  m_listener->p_error.subscribe( &m_subscriber, this, &Server::exitServer );
  m_reactor->inject( m_listener );
  m_reactor->start();
}

void Server::addClient( std::shared_ptr<async::SocketIf> socket ) {
  
  m_client.reset();
  m_client = socket;
  
  m_client->p_error.subscribe( &m_subscriber, [&]() {
    m_reactor->finally( [&](){
      m_client.reset();
    });
  });
  
  m_client->p_read.subscribe( &m_subscriber, [&]( size_t size, const uint8_t* data ) {
    logger::info( "async.example.server" ) << "Echo of " << size << " bytes with count " << static_cast<int>( data[0] );
    m_client->write( size, data );
  });
  
  m_reactor->inject( socket );
}

void Server::exitServer() {
  m_reactor->stop();
}

int main( int argc, char **argv ) {

  std::string ip = "127.0.0.1";
  std::string port = "7575";
  try {
	cli::Parser parser;
	parser.addOption( ip, "a", "address" );
	parser.addOption( port, "p", "port" );
	parser.parseArgs( argc, argv );
  }
  catch( std::exception& e ) {
    std::exit(-1);
  }

  logger::Logger::get().addSink( std::shared_ptr<logger::SinkIf>( new logger::StdStreamSink() ) );
  logger::Logger::get().setLevel( logger::lDEBUG );
  try {
    Server server( ip, port );
  }
  catch( std::exception& e ) {
  }
  logger::Logger::get().clearSinks();
}
