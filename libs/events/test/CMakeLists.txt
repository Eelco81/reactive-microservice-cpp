
add_executable(
  events-tester
  events-serializer-tester.cc
  events-processor-tester.cc
  events-socket-processor-tester.cc
)

target_link_libraries(
  events-tester
  events
  asyncmock
  testmain
)

gtest_discover_tests(events-tester)
