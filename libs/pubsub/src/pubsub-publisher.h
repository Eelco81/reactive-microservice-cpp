
#ifndef _PUBSUB_PUBLISHER_H_
#define _PUBSUB_PUBLISHER_H_

#include <map>
#include <functional>
#include "pubsub-subscriber.h"

namespace pubsub {

class PublisherIf {
public:
  virtual void unsubscribe( Subscriber* ) = 0;
};

template <class ...Args>
class Publisher : public PublisherIf {

public:

  ~Publisher() {
    for ( auto& [sub, callback] : m_callbacks ) {
      sub->unregisterPub( this );
    }
  }

  void publish( Args... args ) {
    for ( auto& [key, callback] : m_callbacks ) {
      callback( args... );
    }
  }

  void subscribe( Subscriber* t_sub, std::function<void( Args... )> t_callback ) {
    t_sub->registerPub( this );
    m_callbacks[t_sub] = t_callback ;
  }

  template <typename T>
  void subscribe( Subscriber* t_sub, T* t_obj, void( T::*t_method )( Args... ) ) {
    return subscribe( t_sub, [t_obj, t_method](Args...args) { ( t_obj->*t_method )( args... ); });
  }

  void forward( Subscriber* t_sub, Publisher& t_pub ) {
    return subscribe( t_sub, [&t_pub](Args...args) { t_pub.publish( args... ); });
  }
  
  void unsubscribe( Subscriber* t_sub ) override {
    m_callbacks.erase( t_sub );
  }

  std::size_t getSubscriptionCount() { return m_callbacks.size(); }

private:

  std::map<Subscriber*, std::function<void(Args...)>> m_callbacks;

};


}

#endif
