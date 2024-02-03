

#ifndef _EVENTS_SERIALIZER_H_
#define _EVENTS_SERIALIZER_H_

#include <pubsub.h>
#include <vector>
#include <cstdint>
#include <string>

namespace events {

struct Header {
  uint32_t m_size = 0;
};

class Deserializer {

public:
  void decode( size_t size, const uint8_t* data );
  void decode( const std::vector<uint8_t>& data );
  pubsub::Publisher<std::size_t, const uint8_t*> p_newData;

protected:
  std::vector<uint8_t> m_buffer;
  constexpr static std::size_t m_headerSize = sizeof( Header );
};

class Serializer {

public:
  std::vector<uint8_t> encode( size_t size, const uint8_t* data );
  std::vector<uint8_t> encode( const std::vector<uint8_t>& data );

protected:
  constexpr static std::size_t m_headerSize = sizeof( Header );
};

} // async

#endif
