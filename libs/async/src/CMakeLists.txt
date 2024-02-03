
project(async)
add_library(async STATIC async-sys.cc async-reactor.cc async-pipe.cc async-socket.cc async-socketpair.cc async-listener.cc)
target_link_libraries(async PUBLIC pubsub logger loggermock)
target_include_directories(async PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})