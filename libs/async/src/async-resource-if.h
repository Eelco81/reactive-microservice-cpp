
#ifndef _ASYNC_RESOURCE_IF_H_
#define _ASYNC_RESOURCE_IF_H_

namespace async {

class ResourceIf {

public:
  virtual ~ResourceIf() = default;
  virtual int getFd() const = 0;
  virtual void handleRead() = 0;
  virtual void handleWrite() = 0;
  virtual void handleError() = 0;

};

} // async

#endif
