
#ifndef _ASYNC_LISTENER_H_
#define _ASYNC_LISTENER_H_

#include "async-resource-if.h"
#include "async-socket.h"
#include <pubsub.h>

#include <memory>
#include <vector>

namespace async {

class ListenerIf : public ResourceIf {
public:
  virtual ~ListenerIf() = default;
  pubsub::Publisher<std::shared_ptr<SocketIf>> p_read;
  pubsub::Publisher<> p_write;
  pubsub::Publisher<> p_error;
public:
  virtual void close() = 0;
};

class ListenerFactoryIf {
public:
  virtual ~ListenerFactoryIf() = default;
  virtual std::shared_ptr<ListenerIf> build() = 0;
};

class ListenerFactory : public ListenerFactoryIf {
public:
  ListenerFactory( const std::string& address, uint16_t port );
  virtual ~ListenerFactory() = default;
  std::shared_ptr<ListenerIf> build( ) override;
private:
  const std::string m_address;
  uint16_t m_port;
};


class ConnectedSocketFactoryIf {
public:
  virtual ~ConnectedSocketFactoryIf() = default;
  virtual std::shared_ptr<SocketIf> build( int fd ) = 0;
};

class ConnectedSocketFactory : public ConnectedSocketFactoryIf {
public:
  virtual ~ConnectedSocketFactory() = default;
  std::shared_ptr<SocketIf> build( int fd ) override;
};

class Listener : public ListenerIf {

public:
  Listener( int fd, std::shared_ptr<ConnectedSocketFactoryIf> factory );
  ~Listener();
  
  // Resource operations
  void close() override;
  
  // ResourceIf implementation
  int getFd() const override;
  void handleRead() override;
  void handleWrite() override;
  void handleError() override;

protected:
  int m_fd;
  std::shared_ptr<ConnectedSocketFactoryIf> m_factory;
  const std::string m_context;
};

} // async

#endif
