
#include <gtest/gtest.h>
#include "diffeq-mesh.h"

TEST( DiffEqTest, Mesh1d ) {
  diffeq::Mesh mesh( 0.0, 10.0, 100u );
  EXPECT_EQ( mesh.data().size(), 100u );
  EXPECT_EQ( mesh.data()[0], 0.0 );
  EXPECT_NEAR( mesh.data()[99], 10.0, 1e-5 );
}
