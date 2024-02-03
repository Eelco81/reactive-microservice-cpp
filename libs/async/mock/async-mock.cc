
#include "async-mock.h"

void async::mock::MockReactor::start() {}
void async::mock::MockReactor::stop() {}
void async::mock::MockReactor::inject( std::shared_ptr<async::ResourceIf> ) {}
void async::mock::MockReactor::finally( std::function<void()> callback ) {
  m_callbacks.push_back( callback );
}
void async::mock::MockReactor::processFinally() {
  for ( auto callback : m_callbacks ) {
    callback();
  }
  m_callbacks.clear();
}

void async::mock::MockPipe::write( size_t size, const uint8_t* data ) { p_read.publish( size, data ); }
void async::mock::MockPipe::close() {}
int async::mock::MockPipe::getFd() const { return 0; }
void async::mock::MockPipe::handleRead() {}
void async::mock::MockPipe::handleWrite() {}
void async::mock::MockPipe::handleError() {}
void async::mock::MockPipe::injectError() { p_error.publish(); }

std::shared_ptr<async::PipeIf> async::mock::MockPipeFactory::build() { 
  auto pipe = std::make_shared<MockPipe>(); 
  m_created.push_back( pipe );
  return pipe;
}

void async::mock::MockSocket::write( size_t size, const uint8_t* data ) { p_read.publish( size, data ); }
void async::mock::MockSocket::close() {}
int async::mock::MockSocket::getFd() const { return 0; }
void async::mock::MockSocket::handleRead() {}
void async::mock::MockSocket::handleWrite() {}
void async::mock::MockSocket::handleError() {}
void async::mock::MockSocket::injectError() { p_error.publish(); }

std::shared_ptr<async::SocketIf> async::mock::MockSocketFactory::build() { 
  auto socket = std::make_shared<MockSocket>(); 
  m_created.push_back( socket );
  return socket;
}

std::shared_ptr<async::SocketIf> async::mock::MockConnectedSocketFactory::build( int ) { 
  auto socket = std::make_shared<MockSocket>(); 
  m_created.push_back( socket );
  return socket;
}
