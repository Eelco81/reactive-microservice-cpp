
#include <cstdio>
#include "gtest/gtest.h"
#include <logger-mock.h>

int main( int argc, char **argv ) {
  
  printf("Running main() from %s\n", __FILE__);
  
  testing::Environment* const env( testing::AddGlobalTestEnvironment( new logger::Env ) );
  
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
