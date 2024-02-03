
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

async::SocketFactory::SocketFactory( const std::string& address, uint16_t port ) :
  m_address{ address },
  m_port{ port }
{
}

std::shared_ptr<async::SocketIf> async::SocketFactory::build() {
  const auto fd = async::system::createSocketFd( m_address, m_port );
  if ( fd <= 0 ) {
    throw std::exception();
  }
  return std::make_shared<Socket>( fd );
}

async::Socket::Socket( int fd ) : 
  m_fd( fd ),
  m_context( "async.socket." + std::to_string( fd ) )
{
  logger::debug( m_context ) << "created";
}

async::Socket::~Socket() {
  logger::debug( m_context ) << "being destroyed";
  close();
}

void async::Socket::write( size_t size, const uint8_t* data ) {
  ::write( m_fd, data, size );
}

void async::Socket::close() {
  if ( m_fd > 0 ) {
    logger::debug( m_context ) << "closing";
    ::shutdown( m_fd, SHUT_RDWR );
    ::close( m_fd );
    m_fd = -1;
  }
}

int async::Socket::getFd() const {
  return m_fd;
}

void async::Socket::handleRead() {
  logger::trace( m_context ) << "handleRead()";
  uint8_t buffer[1000];
  int rtnVal = ::read( m_fd, buffer, 1000 );
  if ( rtnVal < 0 ) {
    logger::error( m_context ) << "read error";
    p_error.publish();
  }
  else if ( rtnVal == 0 ) {
    logger::trace( m_context ) << "not so graceful disconnect";
    p_error.publish();
  }
  else {
    logger::trace( m_context ) << "read ok (" << rtnVal << ")";
    p_read.publish( rtnVal, buffer );
  }
}

void async::Socket::handleWrite() {
  logger::trace( m_context ) << "handleWrite()";
  p_write.publish();
}

void async::Socket::handleError() {
  logger::trace( m_context ) << "handleError()";
  p_error.publish();
}
