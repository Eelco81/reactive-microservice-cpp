
#include <gtest/gtest.h>
#include <thread>

#include <async-reactor.h>
#include <async-listener.h>
#include <async-socket.h>
#include <pubsub.h>

TEST(ReactorTest, ReactorListener) {

  auto reactor = std::make_shared<async::Reactor>();
  auto listener = async::ListenerFactory( "localhost", 1234 ).build();

  std::vector<std::shared_ptr<async::ResourceIf>> clients;

  pubsub::Subscriber subscriber;
  listener->p_read.subscribe( &subscriber, [&clients]( std::shared_ptr<async::ResourceIf> res ) {
    clients.push_back( res ); 
  });

  reactor->inject( listener );
  /*
  std::thread thr([&reactor](){
    reactor->start();
  });
  
  std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
  auto reactor2 = std::make_shared<async::Reactor>();
  auto rclient = async::SocketFactory().build( "localhost", 1234 );
  
  reactor2->inject( rclient );
  reactor2->start();
  */
}