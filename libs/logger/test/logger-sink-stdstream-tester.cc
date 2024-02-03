
#include <sstream>
#include <gtest/gtest.h>
#include <logger-sink-stdstream.h>

using TestParam = std::tuple<logger::Message, std::string>;
class LoggerStdStreamTest : public ::testing::TestWithParam<TestParam> {};

INSTANTIATE_TEST_CASE_P( LoggerStdStreamTest, LoggerStdStreamTest,
  ::testing::Values(
    std::make_tuple( logger::Message( { logger::lFATAL, 0, "hello" } ), std::string( "FATAL [01.01.1970 01:00:00.000] hello\n" ) ),
    std::make_tuple( logger::Message( { logger::lERROR, 1000, "hello" } ), std::string( "ERROR [01.01.1970 01:00:00.001] hello\n" ) ),
    std::make_tuple( logger::Message( { logger::lWARNING, 10000, "hello" } ), std::string( "WARN  [01.01.1970 01:00:00.010] hello\n" ) ),
    std::make_tuple( logger::Message( { logger::lINFO, 100000, "hello" } ), std::string( "INFO  [01.01.1970 01:00:00.100] hello\n" ) ),
    std::make_tuple( logger::Message( { logger::lDEBUG, 1000000, "hello" } ), std::string( "DEBUG [01.01.1970 01:00:01.000] hello\n" ) ),
    std::make_tuple( logger::Message( { logger::lTRACE, 10000000, "hello" } ), std::string( "TRACE [01.01.1970 01:00:10.000] hello\n" ) ),
    std::make_tuple( logger::Message( { logger::lTRACE, 0, "hello", "context" } ), std::string( "TRACE [01.01.1970 01:00:00.000] [context] hello\n" ) )
  )
);

TEST_P( LoggerStdStreamTest, Sink ) {
  std::ostringstream ostr;
  logger::StdStreamSink sink( ostr );
  sink.log( std::get<0>( GetParam() ) );
  EXPECT_EQ( ostr.str(), std::get<1>( GetParam() ) );
}

