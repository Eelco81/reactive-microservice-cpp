
project(logger)
add_library(logger STATIC logger-sink-stdstream.cc logger-sink-fstream.cc logger-types.cc logger.cc)
target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
