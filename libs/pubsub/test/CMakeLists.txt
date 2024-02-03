
add_executable(
  pubsub-tester
  pubsub-tester.cc
)

target_link_libraries(
  pubsub-tester
  pubsub
  testmain
)

gtest_discover_tests(pubsub-tester)
