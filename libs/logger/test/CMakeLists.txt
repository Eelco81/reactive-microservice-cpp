
add_executable(
  logger-tester
  logger-tester.cc
  logger-sink-fstream-tester.cc
  logger-sink-stdstream-tester.cc
)

target_link_libraries(
  logger-tester
  logger
  GTest::gtest_main
  stdc++fs
)

gtest_discover_tests(logger-tester)
