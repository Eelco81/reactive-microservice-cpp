
#ifndef _ASYNC_SYS_H_
#define _ASYNC_SYS_H_

#include <string>

namespace async {
namespace system {

int createListenerFd( const std::string& address, uint16_t port );
int createSocketFd( const std::string& address, uint16_t port );

} // system
} // async

#endif
