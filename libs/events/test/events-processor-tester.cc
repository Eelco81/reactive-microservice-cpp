
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <events-processor.h>
#include <async-mock.h>
#include <pubsub.h>

TEST(EventsTester, Processor) {

  auto reactor = std::make_shared<async::mock::MockReactor>();
  auto factory = std::make_shared<async::mock::MockPipeFactory>();
  auto processor = std::make_shared<events::Processor>( reactor, factory );
  
  const std::vector<uint8_t> payload = { 0x00, 0x01, 0x02, 0x03 };
  std::vector<uint8_t> received;
  
  pubsub::Subscriber sub;
  processor->p_event.subscribe( &sub, [&received]( std::size_t size, const uint8_t* data ) {
    received.assign( data, data + size );
  });
  
  ASSERT_TRUE( processor->write( payload.size(), payload.data() ) );
  ASSERT_EQ( payload, received );
}

TEST(EventsTester, ProcessorReset) {

  auto reactor = std::make_shared<async::mock::MockReactor>();
  auto factory = std::make_shared<async::mock::MockPipeFactory>();
  auto processor = std::make_shared<events::Processor>( reactor, factory );

  ASSERT_TRUE( factory->m_created[0].lock() );
  processor.reset();
  ASSERT_FALSE( factory->m_created[0].lock() );
}

TEST(EventsTester, ProcessorError) {

  auto reactor = std::make_shared<async::mock::MockReactor>();
  auto factory = std::make_shared<async::mock::MockPipeFactory>();
  auto processor = std::make_shared<events::Processor>( reactor, factory );

  ASSERT_TRUE( processor->isAlive() );
  
  {
     auto socket = factory->m_created[0].lock();
     ASSERT_NE( socket, nullptr );
     socket->injectError();
  }
  reactor->processFinally();

  ASSERT_FALSE( processor->isAlive() );
  ASSERT_FALSE( processor->write( 0, {} ) );
  ASSERT_FALSE( factory->m_created[0].lock() );
}

