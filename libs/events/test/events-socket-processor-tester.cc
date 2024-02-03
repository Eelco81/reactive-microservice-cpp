
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <events-socket-processor.h>
#include <async-mock.h>
#include <pubsub.h>

TEST(EventsTester, SocketProcessor) {

  auto reactor = std::make_shared<async::mock::MockReactor>();
  auto factory = std::make_shared<async::mock::MockSocketFactory>();
  auto processor = std::make_shared<events::SocketProcessor>( reactor, factory );
  
  const std::vector<uint8_t> payload = { 0x00, 0x01, 0x02, 0x03 };
  std::vector<uint8_t> received;
  
  pubsub::Subscriber sub;
  processor->p_event.subscribe( &sub, [&received]( std::size_t size, const uint8_t* data ) {
    received.assign( data, data + size );
  });
  
  processor->write( payload.size(), payload.data() );
  
  ASSERT_EQ( payload, received );
}