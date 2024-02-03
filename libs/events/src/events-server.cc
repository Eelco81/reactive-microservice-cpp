
#include "events-server.h"

events::Server::Server( std::shared_ptr<async::ReactorIf> reactor, std::shared_ptr<async::ListenerFactoryIf> listenerFactory, std::shared_ptr<async::ConnectedSocketFactoryIf> socketFactory ) :
  m_reactor{ reactor },
  m_listener{ listenerFactory->build() },
  m_factory{ socketFactory }
{
}
