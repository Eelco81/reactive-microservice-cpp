
#include "logger-sink-fstream.h"

logger::FStreamSink::FStreamSink( const std::string& filename )
{
  m_stream.open( filename );
  m_sink = std::make_unique<StdStreamSink>( m_stream );
}

logger::FStreamSink::~FStreamSink() {
  m_sink.reset();
  m_stream.close();
}

void logger::FStreamSink::log( const logger::Message& message ) {
  m_sink->log( message );
}


