

#include "pubsub-subscriber.h"
#include "pubsub-publisher.h"

pubsub::Subscriber::~Subscriber() {
  for ( auto pub : m_publishers ) {
    pub->unsubscribe( this );
  }
}

void pubsub::Subscriber::registerPub( PublisherIf* t_publisher ) {
  if ( m_publishers.find( t_publisher ) == m_publishers.end() ) {
    m_publishers.insert( t_publisher );
  }
}

void pubsub::Subscriber::unregisterPub( PublisherIf* t_publisher ) {
  m_publishers.erase( t_publisher );
}