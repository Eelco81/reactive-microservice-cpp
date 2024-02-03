
#ifndef _LOGGER_TYPES_H_
#define _LOGGER_TYPES_H_

#include <string>

namespace logger {

using TimePoint = int64_t;

enum Level {
  lFATAL,
  lERROR,
  lWARNING,
  lINFO,
  lDEBUG,
  lTRACE
};

std::string Level2Str( Level level );
std::string TimePoint2Str( TimePoint timepoint );

} // logger

#endif
