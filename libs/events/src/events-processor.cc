
#include "events-processor.h"
#include <logger.h>

namespace {
  const std::string context = "events.processor";
}

events::Processor::Processor( std::shared_ptr<async::ReactorIf> reactor, std::shared_ptr<async::PipeFactoryIf> factory ) :
  m_pipe{ factory->build() },
  m_reactor{ reactor },
  m_serializer{ std::make_shared<Serializer>() },
  m_deserializer{ std::make_shared<Deserializer>() }
{
  m_pipe->p_read.subscribe( &m_subscriber, m_deserializer.get(), &Deserializer::decode );
  m_deserializer->p_newData.forward( &m_subscriber, p_event );
  
  m_pipe->p_error.subscribe( &m_subscriber, [this]() {
    logger::debug( context ) << "Exiting on error";
    this->m_reactor->finally( [this]() { this->m_pipe.reset(); } );
  });
  
  reactor->inject( m_pipe );
}

bool events::Processor::write( size_t size, const uint8_t* data ) {
  if ( m_pipe ) {
    const auto packet = m_serializer->encode( size, data );
    m_pipe->write( packet.size(), packet.data() );
    return true;
  }
  else {
    logger::debug( context ) << "Writing to a broken pipe";
    return false;
  }
}
