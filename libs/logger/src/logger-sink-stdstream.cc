
#include "logger-sink-stdstream.h"

logger::StdStreamSink::StdStreamSink( std::ostream& stream ) :
  m_stream( stream )
{
}

void logger::StdStreamSink::log( const logger::Message& message ){

  std::string context = "";
  if ( message.m_context.size() > 0 ) {
    context = "[" + message.m_context + "] ";
  }

  m_stream << Level2Str( message.m_level ) 
           << " [" << TimePoint2Str( message.m_time )<< "] " 
           << context
           << message.m_data 
           << std::endl;

}

