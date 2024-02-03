
add_executable(
  async-tester
  async-pipe-tester.cc
  async-socketpair-tester.cc
  async-socket-tester.cc
)

target_link_libraries(
  async-tester
  async
  testmain
)

gtest_discover_tests(async-tester)
