
#ifndef _DIFFEQ_ODE_SOLVER_H_
#define _DIFFEQ_ODE_SOLVER_H_

#include "diffeq-mesh.h"
#include "diffeq-func.h"

namespace diffeq {

class OdeSolver {

public:
  OdeSolver( const Mesh& mesh, const Func& func, StateVec x0 );
  std::vector<StateVec> run() const;
 
private:
  Mesh m_mesh;
  Func m_func;
  StateVec m_x0;

};

} // diffeq

#endif

