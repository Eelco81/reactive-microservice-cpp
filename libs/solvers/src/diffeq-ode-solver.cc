
#include "diffeq-ode-solver.h"
#include <iostream>

diffeq::OdeSolver::OdeSolver( const diffeq::Mesh& mesh, const diffeq::Func& func, diffeq::StateVec x0 ) :
  m_mesh( mesh ),
  m_func( func ),
  m_x0( x0 )
{
}

std::vector<diffeq::StateVec> diffeq::OdeSolver::run() const {
  // Solve x'(t) = F(t,x)
  std::vector<StateVec> output( m_mesh.data().size(), m_x0 );
  for( std::size_t i=1; i<output.size(); i++ ) {
    // Euler Forward
    const auto funcOut = m_func( m_mesh.data()[i], output[i-1] );
    for ( std::size_t j=0; j<funcOut.size(); j++ ) { 
      output[i][j] = output[i-1][j] + m_mesh.dt() * funcOut[j];
    }
    // Midpoint Method
    //const auto midpoint = output[k-1] + m_mesh.dt() * m_func( m_mesh.data()[k], output[k-1] ) / 2.0;
    //output[k] = output[k-1] + m_mesh.dt() * m_func( m_mesh.data()[k] + m_mesh.dt()/2.0, midpoint );
  }
  return output;
}
