
#ifndef _ASYNC_PIPE_H_
#define _ASYNC_PIPE_H_

#include "async-resource-if.h"
#include <pubsub.h>

#include <vector>
#include <cstdint>
#include <string>
#include <memory>

namespace async {

class PipeIf : public ResourceIf {
public:
  virtual ~PipeIf() = default;
  pubsub::Publisher<std::size_t, const uint8_t*> p_read;
  pubsub::Publisher<> p_write;
  pubsub::Publisher<> p_error;
public:
  virtual void write( size_t size, const uint8_t* data ) = 0;
  virtual void close() = 0;
};

class PipeFactoryIf {
public:
  virtual ~PipeFactoryIf() = default;
  virtual std::shared_ptr<PipeIf> build() = 0;
};

class PipeFactory : public PipeFactoryIf {
public:
  virtual ~PipeFactory() = default;
  std::shared_ptr<PipeIf> build() override;
};

class Pipe : public PipeIf {

public:
  Pipe();
  ~Pipe();
  
  // PipeIf operations
  void write( size_t size, const uint8_t* data ) override;
  void close() override;
  
  // ResourceIf implementation
  int getFd() const override;
  void handleRead() override;
  void handleWrite() override;
  void handleError() override;

protected:
  int m_fds[2];
  std::string m_context;

};

} // async

#endif
