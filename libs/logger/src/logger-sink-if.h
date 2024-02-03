
#ifndef _LOGGER_SINK_IF_H_
#define _LOGGER_SINK_IF_H_

#include <string>
#include "logger-message.h"

namespace logger {

class SinkIf {

public:
  virtual void log( const Message& ) = 0;

};

} // logger

#endif