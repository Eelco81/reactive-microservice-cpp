
add_executable(
  cli-tester
  cli-tester.cc
)

target_link_libraries(
  cli-tester
  cli
  testmain
)

gtest_discover_tests(cli-tester)
