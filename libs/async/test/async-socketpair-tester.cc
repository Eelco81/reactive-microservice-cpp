
#include <gtest/gtest.h>
#include <thread>

#include <async-reactor.h>
#include <async-socketpair.h>
#include <pubsub.h>

TEST(ReactorTest, ReactorSocketPair) {
  
  auto reactor = std::make_shared<async::Reactor>();
  auto sockets = async::SocketPairFactory().build();
  
  reactor->inject( sockets[0] );
  reactor->inject( sockets[1] );
  
  const std::vector<uint8_t> send = { 0x01, 0x02, 0x03 };
  std::vector<uint8_t> received;
  
  pubsub::Subscriber subscriber;
  sockets[1]->p_read.subscribe( &subscriber, [&received]( size_t size, const uint8_t*data ) {
    received.assign( data, data+size );
  });
  
  std::thread thr([&reactor](){
    reactor->start();
  });
  
  std::this_thread::sleep_for( std::chrono::milliseconds( 300 ) );
  sockets[0]->write( send.size(), send.data() );
  reactor->stop();
  
  // We can only get here if the reactor stopped
  thr.join();

  EXPECT_EQ( received, send );
}

TEST(ReactorTest, ReactorSocketPairError) {
  
  auto reactor = std::make_shared<async::Reactor>();
  auto sockets = async::SocketPairFactory().build();
  
  reactor->inject( sockets[0] );
  
  std::size_t errorCount = 0u;
  auto counter = [&]() { 
    errorCount++;
    // This will remove the socket from the reactor and
    // causing it to exit on empty resources
    reactor->finally( [&]() { sockets[0].reset(); } );
  };
  
  pubsub::Subscriber subscriber;
  sockets[0]->p_error.subscribe( &subscriber, counter );

  std::thread thr([&reactor](){
    reactor->start();
  });
  
  std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
  sockets[1]->close(); 
  
  // We can only get here if the reactor stopped
  thr.join();

  EXPECT_EQ( errorCount, 1u );
}
