
#include "logger-types.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>

std::string logger::Level2Str( Level level ) {

  switch ( level ) {
    case lFATAL : return "FATAL"; break;
    case lERROR : return "ERROR"; break;
    case lWARNING : return "WARN "; break;
    case lINFO : return "INFO "; break;
    case lDEBUG : return "DEBUG"; break;
    case lTRACE : return "TRACE"; break;
    default : break;
  }
  return "";
}

std::string logger::TimePoint2Str( TimePoint timepoint ) {
  TimePoint sec = timepoint / 1000u / 1000u;
  TimePoint usec = timepoint - ( sec * 1000u * 1000u );
  std::time_t now( sec );
  std::tm * ptm = std::localtime( &now );
  char buffer [32];
  std::strftime( buffer, 32, "%d.%m.%Y %H:%M:%S", ptm );
  
  std::ostringstream ostr;
  ostr << buffer << "." << std::setw(3) << std::setfill('0') << usec / 1000u;
  
  return ostr.str() ;
}