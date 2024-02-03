
#include "async-socketpair.h"
#include <logger.h>

#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

std::vector<std::shared_ptr<async::SocketIf>> async::SocketPairFactory::build() {
  int fds[2];
  ::socketpair( AF_UNIX, SOCK_STREAM, 0, fds );
  return { std::make_shared<async::Socket>( fds[0] ), std::make_shared<async::Socket>( fds[1] ) };
}
