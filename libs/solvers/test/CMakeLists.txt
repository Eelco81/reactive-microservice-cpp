
add_executable(
  diffeq-tester
  diffeq-mesh-tester.cc
  diffeq-ode-solver-tester.cc
)

target_link_libraries(
  diffeq-tester
  diffeq
  testmain
)

gtest_discover_tests(diffeq-tester)
