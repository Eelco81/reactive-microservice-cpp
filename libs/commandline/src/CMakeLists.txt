
project(cli)
add_library(cli STATIC cli-parser.cc)
target_link_libraries(cli PUBLIC logger)
target_include_directories(cli PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})