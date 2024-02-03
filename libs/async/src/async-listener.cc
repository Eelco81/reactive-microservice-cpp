
#include "async-listener.h"
#include "async-socket.h"
#include "async-sys.h"
#include <logger.h>

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

async::ListenerFactory::ListenerFactory( const std::string& address, uint16_t port ) :
  m_address{ address },
  m_port{ port }
{
}

std::shared_ptr<async::ListenerIf> async::ListenerFactory::build() {
  const auto fd = async::system::createListenerFd( m_address, m_port );
  if ( fd <= 0 ) {
    throw std::exception();
  }
  return std::make_shared<Listener>( fd, std::make_shared<ConnectedSocketFactory>() );
}

std::shared_ptr<async::SocketIf> async::ConnectedSocketFactory::build( int fd ) {
  return std::make_shared<Socket>( fd );
}

async::Listener::Listener( int fd, std::shared_ptr<ConnectedSocketFactoryIf> factory ) : 
  m_fd{ fd },
  m_factory{ factory },
  m_context( "async.listener." + std::to_string( fd ) )
{
  logger::debug( m_context ) << "created";
}

async::Listener::~Listener() {
  logger::debug( m_context ) << "being destroyed";
  close();
  ::close( m_fd );
}

void async::Listener::close() {
  if ( m_fd > 0 ) {
    logger::debug( m_context ) << "closing";
    ::shutdown( m_fd, SHUT_RDWR );
    m_fd = -1;
  }
}

int async::Listener::getFd() const {
  return m_fd;
}

void async::Listener::handleRead() {
  logger::trace( m_context ) << "handleRead()";
  int fd = ::accept( m_fd, NULL, NULL );
  if ( fd <= 0 ) {
    logger::error( m_context ) << "accept() failed";
    p_error.publish();
    return;
  }
  p_read.publish( m_factory->build( fd ) );
}

void async::Listener::handleWrite() {
  logger::trace( m_context ) << "handleWrite()";
  p_write.publish();
}

void async::Listener::handleError() {
  logger::trace( m_context ) << "handleError()";
  p_error.publish();
}
