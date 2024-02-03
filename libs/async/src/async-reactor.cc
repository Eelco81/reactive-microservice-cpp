
#include "async-reactor.h"
#include "async-resource-if.h"
#include <logger-mock.h>

#include <algorithm>
#include <iostream>
#include <errno.h> 
#include <sys/time.h>

namespace {
const std::string context{ "async.reactor" };
}

void async::Reactor::start() {
  
  logger::debug( context ) << "Starting the loop...";
  
  m_running = true;
  
  while ( m_running & m_resources.size() > 0u ) {
      
    fd_set readFds, writeFds, errorFds;
    FD_ZERO( &readFds );
    FD_ZERO( &writeFds );
    FD_ZERO( &errorFds );
    
    int maxFd = -1;
    for ( auto resource : m_resources ) {
      const auto fd = resource.lock()->getFd();
      FD_SET( fd, &readFds );
      //FD_SET( fd, &writeFds );
      FD_SET( fd, &errorFds );
      maxFd = ( fd > maxFd ? fd : maxFd );
    }
    
    struct timeval timeout;
    timeout.tv_sec = 100;
    timeout.tv_usec = 0;
    
    logger::trace( context ) << "Start wait for activity [" << errno << "] queue[" << m_resources.size() << "]";
    auto retVal = select( maxFd + 1, &readFds, &writeFds, &errorFds, &timeout );
    logger::trace( context ) << "Waking up [" << retVal << "][" << errno << "]";

    if ( ( retVal < 0 ) && ( errno != EINTR ) ) {
      logger::error( context ) << "Select error [" << errno << "] --> " << strerror( errno );
    }
    
    // Delete faulty resources, this can really only happen in multi threaded 
    // applications --> i.e. in some specific unit tests
    // m_resources.erase( std::remove_if( m_resources.begin(), m_resources.end(),
    //  [](auto resource){ return resource->getFd() <= 0; } ), m_resources.end() );
      
    for ( auto resource : m_resources ) {
      auto res = resource.lock();
      if ( FD_ISSET( res->getFd(), &readFds ) ) {
        res->handleRead();
      }
      //if ( FD_ISSET( res->getFd(), &writeFds ) ) {
      //  res->handleWrite();
      //}
      if ( FD_ISSET( res->getFd(), &errorFds ) ) {
        res->handleError();
      }
    }
    
    for ( auto callback : m_callbacks ) {
      callback();
    }
    m_callbacks.clear();
    
    // Delete
    m_resources.erase( std::remove_if( m_resources.begin(), m_resources.end(),
      [](auto resource){ return !resource.lock(); } ), m_resources.end() );
  }
  
  m_resources.clear();
  logger::debug( context ) << "Resource list is empty, exiting the loop";
}

void async::Reactor::stop() {
  logger::debug( context ) << "Request received to stop after the next event";
  m_running = false;
}

void async::Reactor::inject( std::shared_ptr<ResourceIf> resource ) {
  m_resources.push_back( resource );
}

void async::Reactor::finally( std::function<void()> callback ) {
  m_callbacks.push_back( callback );
}

