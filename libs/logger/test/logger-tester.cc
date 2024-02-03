
#include <gtest/gtest.h>
#include <logger.h>
#include <logger-sink-stdstream.h>

namespace { 

class CollectSink : public logger::SinkIf {

public:
  void log( const logger::Message& message ) override {
    m_messages.push_back( message );
  };
  std::vector<logger::Message> m_messages = {};
};

}

TEST( LoggerTest, Message ) {
  
  auto collector = std::shared_ptr<CollectSink>( new CollectSink() );
  logger::Logger::get().addSink( collector );
  
  logger::info() << "Hello " << 1234;
  logger::info( "context" ) << "Hello " << 1234;

  EXPECT_EQ( collector->m_messages.size(), 2u );
  EXPECT_EQ( collector->m_messages[0].m_level, logger::lINFO );
  EXPECT_EQ( collector->m_messages[0].m_data, std::string( "Hello 1234" ) );
  EXPECT_EQ( collector->m_messages[1].m_level, logger::lINFO );
  EXPECT_EQ( collector->m_messages[1].m_data, std::string( "Hello 1234" ) );
  EXPECT_EQ( collector->m_messages[1].m_context, std::string( "context" ) );
    
  logger::Logger::get().clearSinks();

}