
#ifndef _ASYNC_MOCK_H_
#define _ASYNC_MOCK_H_

#include <async.h>
#include <string>

namespace async {
namespace mock {

class MockReactor : public async::ReactorIf {
public:
  void start() override;
  void stop() override;
  void inject( std::shared_ptr<async::ResourceIf> ) override;
  void finally( std::function<void()> ) override;
public:
  void processFinally();
private:
  std::vector<std::function<void()>> m_callbacks;
};

class MockPipe : public async::PipeIf {
public:
  void write( size_t size, const uint8_t* data ) override;
  void close() override;
  int getFd() const override;
  void handleRead() override;
  void handleWrite() override;
  void handleError() override;
public:
  void injectError();
};

class MockPipeFactory : public async::PipeFactoryIf {
public:
  std::shared_ptr<async::PipeIf> build();
public:
  std::vector<std::weak_ptr<MockPipe>> m_created;
};

class MockSocket : public async::SocketIf {
public:
  void write( size_t size, const uint8_t* data ) override;
  void close() override;
  int getFd() const override;
  void handleRead() override;
  void handleWrite() override;
  void handleError() override;
public:
  void injectError();
};

class MockSocketFactory : public async::SocketFactoryIf {
public:
  std::shared_ptr<async::SocketIf> build();
public:
  std::vector<std::weak_ptr<MockSocket>> m_created;
};

class MockConnectedSocketFactory : public async::ConnectedSocketFactoryIf {
public:
  std::shared_ptr<async::SocketIf> build( int fd );
public:
  std::vector<std::weak_ptr<MockSocket>> m_created;
};

} // mock
} // async

#endif
