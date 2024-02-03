
add_executable(
  async-example-server
  async-example-server.cc
)

target_link_libraries(
  async-example-server
  async
  cli
)

add_executable(
  async-example-client
  async-example-client.cc
)

target_link_libraries(
  async-example-client
  async
  cli
)