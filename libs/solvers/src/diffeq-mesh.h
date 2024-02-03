
#ifndef _DIFFEQ_MESH_H_
#define _DIFFEQ_MESH_H_

#include <vector>
#include <cstdint>

namespace diffeq {

class Mesh  {

public:
  Mesh( double t_min, double t_max, std::size_t N );
  const std::vector<double>& data() const { return m_data; };
  const double& dt() const { return m_delta; };

protected:
  std::vector<double> m_data;
  double m_delta;

};

} // async

#endif
