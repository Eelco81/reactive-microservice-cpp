
#include <events-serializer.h> 
#include <cstring>

std::vector<uint8_t> events::Serializer::encode( size_t size, const uint8_t* data ) {

  Header header { static_cast<uint32_t>( size ) };
  
  std::vector<uint8_t> output( size + m_headerSize );
  std::memcpy( output.data(), &header, m_headerSize );
  std::copy( data, data + size, output.data() + m_headerSize );
  
  return output;
}

std::vector<uint8_t> events::Serializer::encode( const std::vector<uint8_t>& data ) {
  return encode( data.size(), data.data() );
}

void events::Deserializer::decode( size_t size, const uint8_t* data ) {
  
  std::copy( data, data + size, std::back_inserter( m_buffer ) );
  
  while( true ) {
    Header header;
    if ( m_buffer.size() < m_headerSize ) {
      return;
    }
    std::memcpy( &header, m_buffer.data(), m_headerSize );
    if( m_buffer.size() < header.m_size + m_headerSize ) {
      return;
    }
    p_newData.publish( header.m_size, m_buffer.data() + m_headerSize );
    m_buffer.erase( m_buffer.begin(), m_buffer.begin() + header.m_size + m_headerSize );
  }
}

void events::Deserializer::decode( const std::vector<uint8_t>& data ) {
  decode( data.size(), data.data() );
}
