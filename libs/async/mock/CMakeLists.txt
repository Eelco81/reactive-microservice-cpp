
add_library(asyncmock STATIC async-mock.cc)
target_link_libraries(asyncmock PUBLIC async GTest::gtest)
target_include_directories(asyncmock PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
