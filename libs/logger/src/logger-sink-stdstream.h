
#ifndef _LOGGER_SINK_STDSTREAM_H_
#define _LOGGER_SINK_STDSTREAM_H_

#include <iostream>
#include "logger-sink-if.h"

namespace logger {

class StdStreamSink : public SinkIf {

public:
  StdStreamSink( std::ostream& stream = std::cout );
  void log( const Message& ) override;

private:
  std::ostream& m_stream;

};

} // logger

#endif
