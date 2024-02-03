
project(diffeq)
add_library(diffeq STATIC diffeq-mesh.cc diffeq-ode-solver.cc)
target_link_libraries(diffeq PUBLIC logger loggermock)
target_include_directories(diffeq PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})