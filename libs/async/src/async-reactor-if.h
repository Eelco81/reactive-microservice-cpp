
#ifndef _ASYNC_REACTOR_IF_H_
#define _ASYNC_REACTOR_IF_H_

#include <memory>
#include <functional>

namespace async {

class ResourceIf;

class ReactorIf {

public:
  virtual ~ReactorIf() = default;
  virtual void start() = 0;
  virtual void stop() = 0;
  virtual void inject( std::shared_ptr<ResourceIf> resourceIf ) = 0;
  virtual void finally( std::function<void()> callback ) = 0;
};

} // async

#endif
