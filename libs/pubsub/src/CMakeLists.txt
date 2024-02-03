
project(pubsub)
add_library(pubsub STATIC pubsub-publisher.cc pubsub-subscriber.cc)
target_include_directories(pubsub PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
