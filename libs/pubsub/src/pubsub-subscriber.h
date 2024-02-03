
#ifndef _PUBSUB_SUBSCRIBER_H_
#define _PUBSUB_SUBSCRIBER_H_

#include <set>

namespace pubsub {

class PublisherIf;

class Subscriber {

public:
  ~Subscriber();
  void registerPub( PublisherIf* t_publisher );
  void unregisterPub( PublisherIf* t_publisher );
   
  std::size_t getPublisherCount() { return m_publishers.size(); }

protected:
  std::set<PublisherIf*> m_publishers;

};

}

#endif
