
#include "async-sys.h"
#include "logger.h"

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

namespace {

enum Type {
  SERVER = 0,
  CLIENT = 1
};

int createFd( const std::string& address, uint16_t port, Type type ) {

  struct addrinfo hints;
  struct addrinfo *addrInfo;

#if (defined __CYGWIN__ || defined __GNUC__)
  ::memset( &hints, 0, sizeof( hints ) );
#else
  ZeroMemory( &hints, sizeof( hints ) );
#endif
  
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  // Resolve the server address and port
  if ( ::getaddrinfo( address.c_str (), std::to_string( port ).c_str(), &hints, &addrInfo ) < 0 ) {
    logger::error() << "getaddrinfo() failed";
    return -1;
  }
  
  // Create a SOCKET for connecting to server
  int fd = socket( addrInfo->ai_family, addrInfo->ai_socktype, addrInfo->ai_protocol );
  if ( fd <= 0 ) {
    logger::error() << "socket() failed";
    return -1;
  }
  
  int flag( 1 );
#if (defined __CYGWIN__ || defined __GNUC__)
  if ( setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&flag), sizeof(flag) ) < 0 ) {
#else
  if ( setsockopt( fd, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, reinterpret_cast<char*>(&flag), sizeof(flag) ) < 0 ) {
#endif
    logger::error() << "setsockopt() failed";
    return -1;
  }
  
  if (type == SERVER) {
    if ( ::bind( fd, addrInfo->ai_addr, (int)addrInfo->ai_addrlen ) < 0 ) {
      logger::error() << "bind() failed";
      return -1;
    }
    if ( ::listen( fd, 10 ) < 0 ) {
      logger::error() << "listen() failed";
      return -1;
    }
  }
  else {
    if ( ::connect( fd, addrInfo->ai_addr, (int)addrInfo->ai_addrlen ) < 0 ) {
      logger::error() << "connect() failed";
      return -1;
    }
  }
  
  return fd;
}

}

int async::system::createListenerFd( const std::string& address, uint16_t port ) {
  return createFd( address, port, SERVER );
}

int async::system::createSocketFd( const std::string& address, uint16_t port ) {
  return createFd( address, port, CLIENT );
}
