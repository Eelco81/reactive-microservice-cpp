
#ifndef _LOGGER_BUFFER_H_
#define _LOGGER_BUFFER_H_

#include <string>
#include <sstream>
#include <chrono>

namespace logger {

template<Level level>
class Buffer {

public:
  
  Buffer( const std::string& context = "" ) :
    m_context( context ) 
  {
  }
  
  ~Buffer() {
    const auto now( std::chrono::high_resolution_clock::now() );
    const auto duration( now.time_since_epoch() );
    const auto timepoint( std::chrono::duration_cast<std::chrono::microseconds>( duration ).count() );
    Logger::get().log( { level, timepoint, m_stream.str (), m_context } );
  };

  template <typename T>
  Buffer& operator<<( const T& inValue ) {
    m_stream << inValue;
    return *this;
  }
    
private:
  std::stringstream m_stream;
  const std::string m_context;
};

} // logger

#endif