
#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include <vector>
#include <memory>

#include "logger-types.h"
#include "logger-message.h"
#include "logger-sink-if.h"

namespace logger {

class Logger {
  
public:
  
  static Logger& get() {
    static Logger instance;
    return instance;
  }
  
  void log( const Message& message );

  void addSink( const std::shared_ptr<SinkIf>& sink ); 
  void clearSinks();
  void setLevel( Level level );
  
private:
  Logger() = default;
  std::vector<std::shared_ptr<SinkIf>> m_sinks = {};
  Level m_level = lINFO;
  
};

}

#include "logger-buffer.h"

namespace logger {

using fatal = Buffer<lFATAL>;
using error = Buffer<lERROR>;
using warning = Buffer<lWARNING>;
using info = Buffer<lINFO>;
using debug = Buffer<lDEBUG>;
using trace = Buffer<lTRACE>;

} // logger

#endif
