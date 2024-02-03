
#ifndef _EVENTS_SOCKET_PROCESSOR_H_
#define _EVENTS_SOCKET_PROCESSOR_H_

#include "events-serializer.h"
#include <pubsub.h>
#include <async.h>
#include <cstdint>
#include <string>

namespace events {

class SocketProcessor {

public:
  SocketProcessor( std::shared_ptr<async::ReactorIf> reactor, std::shared_ptr<async::SocketFactoryIf> factory );
  void write( size_t size, const uint8_t* data );

public:
  pubsub::Publisher<std::size_t, const uint8_t*> p_event;
  
protected:
  std::shared_ptr<async::SocketIf> m_socket;
  std::shared_ptr<Serializer> m_serializer;
  std::shared_ptr<Deserializer> m_deserializer;
  pubsub::Subscriber m_subscriber;

};

}

#endif
