
#ifndef _ASYNC_REACTOR_H_
#define _ASYNC_REACTOR_H_

#include "async-reactor-if.h"

#include <vector>
#include <memory>
#include <functional>

namespace async {

class Reactor : public ReactorIf {

public:
  void start() override;
  void stop() override;
  void inject( std::shared_ptr<ResourceIf> resourceIf ) override;
  void finally( std::function<void()> callback ) override;
  
protected:
  std::vector<std::weak_ptr<ResourceIf>> m_resources;
  std::vector<std::function<void()>> m_callbacks;
  bool m_running = false;
 
};

} // async

#endif
