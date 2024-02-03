
#include <gtest/gtest.h>
#include "diffeq-ode-solver.h"

TEST( DiffEqTest, OdeSolver1 ) {
  diffeq::Mesh mesh( 0.0, 2.0, 100u );
  diffeq::Func func = [](double t, const diffeq::StateVec& x) { return diffeq::StateVec{ 1.0 }; };
  diffeq::OdeSolver solver( mesh, func, { 0.0 } );
  const auto data = solver.run();
  EXPECT_EQ( 100, data.size() );
  EXPECT_NEAR( 0.0, data[0][0], 1e-5 );
  EXPECT_NEAR( 2.0, data[99][0], 1e-5 );
  for (auto d : data ) {
    std::cout << d[0] << " ";
  }
  std::cout<<std::endl;
}

TEST( DiffEqTest, OdeSolver2 ) {
  diffeq::Mesh mesh( 0.0, 2.0, 100u );
  diffeq::Func func = [](double t, const diffeq::StateVec& x) { return diffeq::StateVec{ -10.0*x[0] }; };
  diffeq::OdeSolver solver( mesh, func, { 1.0 } );
  const auto data = solver.run();
  EXPECT_EQ( 100, data.size() );
  EXPECT_NEAR( 1.0, data[0][0], 1e-5 );
  EXPECT_NEAR( 0.0, data[99][0], 1e-5 );
  for (auto d : data ) {
    std::cout << d[0] << " ";
  }
  std::cout<<std::endl;
}

TEST( DiffEqTest, OdeSolver3 ) {
  diffeq::Mesh mesh( 0.0, 2.0, 1000u );
  diffeq::Func func = [](double t, const diffeq::StateVec& x) { 
    return diffeq::StateVec{ x[1], (-x[0]-0.1*x[1])/0.01 }; 
  };
  diffeq::OdeSolver solver( mesh, func, { 1.0, 0.0 } );
  const auto data = solver.run();
  EXPECT_EQ( 1000, data.size() );
  EXPECT_NEAR( 1.0, data[0][0], 1e-3 );
  EXPECT_NEAR( 0.0, data[999][0], 1e-3 );
  for (auto d : data ) {
    std::cout << d[0] << " ";
  }
  std::cout<<std::endl;
}
