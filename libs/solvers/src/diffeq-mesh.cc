
#include "diffeq-mesh.h"
#include <algorithm>

diffeq::Mesh::Mesh( double t_min, double t_max, std::size_t N ) :
  m_delta( ( t_max - t_min )/static_cast<double>( N-1 ) )
{
  m_data.resize( N );
  m_data[0] = t_min;
  for( std::size_t k=1; k<N; k++ ) {
    m_data[k] = m_data[k-1] + m_delta;
  }
}