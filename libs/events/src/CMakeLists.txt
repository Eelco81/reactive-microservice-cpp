
project(events)
add_library(events STATIC events-serializer.cc events-processor.cc events-socket-processor.cc events-server.cc)
target_link_libraries(events PUBLIC async pubsub logger loggermock)
target_include_directories(events PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
