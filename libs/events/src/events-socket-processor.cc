
#include "events-socket-processor.h"
#include <logger.h>

events::SocketProcessor::SocketProcessor( std::shared_ptr<async::ReactorIf> reactor, std::shared_ptr<async::SocketFactoryIf> factory ) :
  m_socket{ factory->build() },
  m_serializer{ std::make_shared<Serializer>() },
  m_deserializer{ std::make_shared<Deserializer>() }
{
  m_socket->p_read.subscribe( &m_subscriber, m_deserializer.get(), &Deserializer::decode );
  m_deserializer->p_newData.forward( &m_subscriber, p_event );
  
  m_socket->p_error.subscribe( &m_subscriber, [&reactor, this]() {
    logger::debug( "events.socket.processor" ) << "Exiting";
    reactor->finally( [this]() { this->m_socket.reset(); } );
  });
  
  reactor->inject( m_socket );
}

void events::SocketProcessor::write( size_t size, const uint8_t* data ) {
  if ( m_socket ) {
    const auto packet = m_serializer->encode( size, data );
    m_socket->write( packet.size(), packet.data() );
  }
  else {
    logger::debug( "events.socket.processor" ) << "Writing to a broken socket";
  }
}
