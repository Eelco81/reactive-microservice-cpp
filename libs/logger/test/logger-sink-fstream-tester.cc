
#include <sstream>
#include <gtest/gtest.h>
#include <logger-sink-fstream.h>
#include <experimental/filesystem>
namespace filesystem = std::experimental::filesystem;

TEST( LoggerFStreamTest, Sink ) {
  
  const std::string path( "./temp.txt" );
  const auto fsPath = filesystem::path( path );
  EXPECT_FALSE( filesystem::exists( fsPath ) );
  
  {
    logger::FStreamSink sink( path );
    sink.log( { logger::lINFO, 0, "log!" } );
    sink.log( { logger::lINFO, 0, "another log!" } ); 
  } // make sure the sink goes out of scope, calls destructor
  
  EXPECT_TRUE( filesystem::exists( fsPath ) );
  EXPECT_TRUE( filesystem::is_regular_file( fsPath ) );
  
  std::ifstream str( path );
  std::string logData(
    ( std::istreambuf_iterator<char>( str ) ),
    std::istreambuf_iterator<char>()
  );
  
  EXPECT_EQ( std::string( "INFO  [01.01.1970 01:00:00.000] log!\nINFO  [01.01.1970 01:00:00.000] another log!\n" ), logData ); 
  
  filesystem::remove_all( fsPath ); 
  EXPECT_FALSE( filesystem::exists( fsPath ) );
  
}
