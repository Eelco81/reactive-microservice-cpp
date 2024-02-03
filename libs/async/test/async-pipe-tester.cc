
#include <gtest/gtest.h>
#include <thread>

#include <async-reactor.h>
#include <async-pipe.h>
#include <pubsub.h>

TEST(ReactorTest, ReactorPipe) {
  
  auto reactor = std::make_shared<async::Reactor>();
  auto pipe = async::PipeFactory().build();
  reactor->inject( pipe );
  
  const std::vector<uint8_t> send = { 0x01, 0x02, 0x03 };
  std::vector<uint8_t> received;
  
  pubsub::Subscriber subscriber;
  pipe->p_read.subscribe( &subscriber, [&received](size_t size, const uint8_t*data ) {
    received.assign( data, data+size );
  });
  
  std::thread thr([&reactor](){
    reactor->start();
  });
  
  std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
  pipe->write( send.size(), send.data() );
  
  reactor->stop();
  thr.join();

  EXPECT_EQ( received, send );
}

TEST(ReactorTest, ReactorPipeError) {

  auto reactor = std::make_shared<async::Reactor>();
  auto pipe = async::PipeFactory().build();
  reactor->inject( pipe );
  
  std::size_t errorCount = 0u;
  
  pubsub::Subscriber subscriber;
  pipe->p_error.subscribe( &subscriber, [&]() {
    errorCount++;
    // This will remove the socket from the reactor and
    // causing it to exit on empty resources
    reactor->finally( [&]() { pipe.reset(); } );
  });

  std::thread thr([&reactor](){
    reactor->start();
  });
  
  std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
  pipe->close();
  std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
  
  thr.join();
  
  EXPECT_EQ( errorCount, 1u );
}