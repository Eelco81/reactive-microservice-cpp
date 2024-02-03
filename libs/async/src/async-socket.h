
#ifndef _ASYNC_SOCKET_H_
#define _ASYNC_SOCKET_H_

#include "async-resource-if.h"
#include <pubsub.h>

#include <memory>
#include <vector>
#include <cstdint>
#include <string>

namespace async {

class SocketIf : public ResourceIf {
public:
  virtual ~SocketIf() = default;
  pubsub::Publisher<std::size_t, const uint8_t*> p_read;
  pubsub::Publisher<> p_write;
  pubsub::Publisher<> p_error;
public:
  virtual void write( size_t size, const uint8_t* data ) = 0;
  virtual void close() = 0;
};

class SocketFactoryIf {
public:
  virtual ~SocketFactoryIf() = default;
  virtual std::shared_ptr<SocketIf> build() = 0;
};

class SocketFactory : public SocketFactoryIf {
public:
  SocketFactory( const std::string& address, uint16_t port );
  std::shared_ptr<SocketIf> build() override;
private:
  const std::string m_address;
  uint16_t m_port;
};

class Socket : public SocketIf {

public:
  Socket( int fd );
  ~Socket();
  
  // Resource operations
  void write( size_t size, const uint8_t* data );
  void close();
  
  // ResourceIf implementation
  int getFd() const override;
  void handleRead() override;
  void handleWrite() override;
  void handleError() override;

protected:
  int m_fd;
  const std::string m_context;

};

} // async

#endif
