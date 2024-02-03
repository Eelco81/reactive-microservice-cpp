
add_library(loggermock STATIC logger-mock.cc)
target_link_libraries(loggermock PUBLIC logger GTest::gtest)
target_include_directories(loggermock PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
