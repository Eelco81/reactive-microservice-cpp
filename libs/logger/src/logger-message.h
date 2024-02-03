
#ifndef _LOGGER_MESSAGE_H_
#define _LOGGER_MESSAGE_H_

#include "logger-types.h"

namespace logger {

struct Message {
  Level m_level = lINFO;
  TimePoint m_time = 0u;
  std::string m_data = "";
  std::string m_context = "";
};

} // logger

#endif
