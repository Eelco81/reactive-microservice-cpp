
#include "async-pipe.h"
#include <logger.h>

#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

std::shared_ptr<async::PipeIf> async::PipeFactory::build() {
  return std::make_shared<Pipe>();
}

async::Pipe::Pipe() {
  ::pipe( m_fds );
  m_context = "async.pipe." + std::to_string( m_fds[0] ) + "." +std::to_string( m_fds[1] );
  logger::debug( m_context ) << "created";
}

async::Pipe::~Pipe() {
  logger::trace( m_context ) << "entering destructor";
  close();
  logger::trace( m_context ) << "closing reader";
  ::close( m_fds[0] );
}

void async::Pipe::write( size_t size, const uint8_t* data ) {
  ::write( m_fds[1], data, size );
}

void async::Pipe::close() {
  if ( m_fds[1] > 0 ) {
    logger::debug( m_context ) << "closing writer";
    ::close( m_fds[1] );
    m_fds[1] = -1;
  }
}

int async::Pipe::getFd() const {
  return m_fds[0];
}

void async::Pipe::handleRead() {
  logger::trace( m_context ) << "handleRead()";
  uint8_t buffer[1000];
  int rtnVal = ::read( m_fds[0], buffer, 1000 );
  if ( rtnVal < 0 ) {
    logger::error( m_context ) << "read error";
  }
  else {
    logger::trace( m_context ) << "read ok (" << rtnVal << ")";
    p_read.publish( rtnVal, buffer );
  }
}

void async::Pipe::handleWrite() {
  logger::trace( m_context ) << "handleWrite()";
  p_write.publish();
}

void async::Pipe::handleError() {
  logger::trace( m_context ) << "handleError()";
  p_error.publish();
}