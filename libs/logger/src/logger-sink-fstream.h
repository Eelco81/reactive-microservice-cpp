
#ifndef _LOGGER_SINK_FSTREAM_H_
#define _LOGGER_SINK_FSTREAM_H_

#include <fstream>
#include <memory>
#include <string>

#include "logger-sink-if.h"
#include "logger-sink-stdstream.h"

namespace logger {

class FStreamSink : public SinkIf {

public:
  FStreamSink( const std::string& filename );
  ~FStreamSink();
  void log( const Message& ) override;

private:
  std::unique_ptr<StdStreamSink> m_sink;
  std::ofstream m_stream;
};

} // logger

#endif
