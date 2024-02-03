
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <events-serializer.h>
#include <pubsub.h>

TEST(EventsTester, SerializerWithoutPayload) {
  events::Serializer serializer;
  std::vector<uint8_t> data = serializer.encode( { } );
  ASSERT_THAT( data, ::testing::ElementsAre(0,0,0,0) );
}

TEST(EventsTester, SerializerWithPayload) {
  events::Serializer serializer;
  std::vector<uint8_t> data = serializer.encode( { 0x00, 0x01, 0x02, 0x03 } );
  ASSERT_THAT( data, ::testing::ElementsAre(4,0,0,0,0,1,2,3) );
}

TEST(EventsTester, Deserializer) {
  
  const std::vector<uint8_t> payload = { 0x00, 0x01, 0x02, 0x03 };
  
  events::Serializer serializer;
  std::vector<uint8_t> data = serializer.encode( payload );
  
  events::Deserializer deserializer;
  pubsub::Subscriber sub;
  std::vector<uint8_t> received;
  deserializer.p_newData.subscribe( &sub, [&received]( std::size_t size, const uint8_t* data ) {
    received.assign( data, data + size );
  });
  deserializer.decode( data );
  
  ASSERT_EQ( received, payload );
}

TEST(EventsTester, DeserializerByteByByte) {
  
  const std::vector<uint8_t> payload = { 0x00, 0x01, 0x02, 0x03 };
  
  events::Serializer serializer;
  std::vector<uint8_t> data = serializer.encode( payload );
  
  events::Deserializer deserializer;
  pubsub::Subscriber sub;
  std::vector<uint8_t> received;
  deserializer.p_newData.subscribe( &sub, [&received]( std::size_t size, const uint8_t* data ) {
    received.assign( data, data + size );
  });
  
  for ( auto e : data ) {
    deserializer.decode( { e } );
  }
  
  ASSERT_EQ( received, payload );
}


TEST(EventsTester, DeserializerMultiPacket) {
  
  const std::vector<uint8_t> payload = { 0x00, 0x01, 0x02, 0x03 };
  
  events::Serializer serializer;
  std::vector<uint8_t> data = serializer.encode( payload );
  
  events::Deserializer deserializer;
  pubsub::Subscriber sub;
  std::vector<std::vector<uint8_t>> received;
  deserializer.p_newData.subscribe( &sub, [&received]( std::size_t size, const uint8_t* data ) {
    std::vector<uint8_t> temp;
    temp.assign( data, data + size );
    received.push_back( temp );
  });
  
  std::vector<uint8_t> stream = data;
  std::copy( data.begin(), data.end(), std::back_inserter( stream ) );
  deserializer.decode( stream );
  
  ASSERT_EQ( received.size(), 2 );
  ASSERT_EQ( received[0], payload );
  ASSERT_EQ( received[1], payload );
}
