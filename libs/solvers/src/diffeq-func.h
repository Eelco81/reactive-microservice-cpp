
#ifndef _DIFFEQ_FUNC_H_
#define _DIFFEQ_FUNC_H_

#include <functional>

namespace diffeq {

// F(t,x)
using StateVec = std::vector<double>;
using Func = std::function<StateVec(double,const StateVec&)>;

} // diffeq

#endif
