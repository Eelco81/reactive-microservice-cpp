
#ifndef _EVENTS_PROCESSOR_H_
#define _EVENTS_PROCESSOR_H_

#include "events-serializer.h"
#include <pubsub.h>
#include <async.h>
#include <cstdint>
#include <string>

namespace events {

class Processor {

public:
  Processor( std::shared_ptr<async::ReactorIf> reactor, std::shared_ptr<async::PipeFactoryIf> factory );
  bool write( size_t size, const uint8_t* data );
  bool isAlive() const { return m_pipe != nullptr; }

public:
  pubsub::Publisher<std::size_t, const uint8_t*> p_event;
  
protected:
  std::shared_ptr<async::PipeIf> m_pipe;
  std::shared_ptr<async::ReactorIf> m_reactor;
  std::shared_ptr<Serializer> m_serializer;
  std::shared_ptr<Deserializer> m_deserializer;
  pubsub::Subscriber m_subscriber;

};

}

#endif
