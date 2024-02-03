
#ifndef _EVENTS_SERVER_H_
#define _EVENTS_SERVER_H_

#include <pubsub.h>
#include <async.h>
#include <cstdint>
#include <string>

namespace events {

class Server {

public:
  Server( std::shared_ptr<async::ReactorIf> reactor, std::shared_ptr<async::ListenerFactoryIf> listenerFactory, std::shared_ptr<async::ConnectedSocketFactoryIf> socketFactory );
  void broadcast( size_t size, const uint8_t* data );

protected:
  std::shared_ptr<async::ReactorIf> m_reactor;
  std::shared_ptr<async::ListenerIf> m_listener;
  std::shared_ptr<async::ConnectedSocketFactoryIf> m_factory;
  pubsub::Subscriber m_subscriber;

};

}

#endif
