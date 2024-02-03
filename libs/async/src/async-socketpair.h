
#ifndef _ASYNC_SOCKETPAIR_H_
#define _ASYNC_SOCKETPAIR_H_

#include "async-resource-if.h"
#include "async-socket.h"
#include <pubsub.h>

#include <memory>
#include <vector>
#include <cstdint>
#include <string>

namespace async {

class SocketPairFactory {

public:
  std::vector<std::shared_ptr<SocketIf>> build();

};

} // async

#endif
