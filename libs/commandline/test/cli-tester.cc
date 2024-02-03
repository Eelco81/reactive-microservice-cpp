
#include <gtest/gtest.h>
#include <cli-parser.h>
#include <tuple>

TEST(CliTest, NoOptionsShouldNotThrow) {

  const int argc = 1;
  const char* const argv[argc] = { "program_name" };

  cli::Parser parser;
  parser.parseArgs( argc, argv );
}

TEST(CliTest, SettingBooleanShortFlags) {

  const int argc = 2;
  const char* const argv[argc] = { "program_name", "-x" };

  bool x = false;
  bool y = false;

  cli::Parser parser;
  parser.addFlag( x, "x", "x_x_x" );
  parser.addFlag( y, "y", "y_y_y" );
  parser.parseArgs( argc, argv );

  ASSERT_TRUE( x );
  ASSERT_FALSE( y );
}

TEST(CliTest, SettingBooleanLongFlags) {

  const int argc = 2;
  const char* const argv[argc] = { "program_name", "--x_x_x" };

  bool x = false;
  bool y = false;

  cli::Parser parser;
  parser.addFlag( x, "x", "x_x_x" );
  parser.addFlag( y, "y", "y_y_y" );
  parser.parseArgs( argc, argv );

  ASSERT_TRUE( x );
  ASSERT_FALSE( y );
}

TEST(CliTest, SettingShortOptions) {

  const int argc = 3;
  const char* const argv[argc] = { "program_name", "-x", "2" };

  std::string x = "0";
  std::string y = "0";

  cli::Parser parser;
  parser.addOption( x, "x", "x_x_x" );
  parser.addOption( y, "y", "y_y_y" );
  parser.parseArgs( argc, argv );

  ASSERT_EQ( x, "2" );
  ASSERT_EQ( y, "0" );
}

TEST(CliTest, SettingLongOptions) {

  const int argc = 3;
  const char* const argv[argc] = { "program_name", "--x_x_x", "2" };

  std::string x = "0";
  std::string y = "0";

  cli::Parser parser;
  parser.addOption( x, "x", "x_x_x" );
  parser.addOption( y, "y", "y_y_y" );
  parser.parseArgs( argc, argv );

  ASSERT_EQ( x, "2" );
  ASSERT_EQ( y, "0" );
}

using TestParam = std::tuple<std::string>;
class CliErrorTest : public ::testing::TestWithParam<TestParam> {};

INSTANTIATE_TEST_CASE_P( CliErrorTest, CliErrorTest,
  ::testing::Values(
    std::make_tuple( std::string("-too_long") ),
    std::make_tuple( std::string("-") ),
    std::make_tuple( std::string("--") ),
    std::make_tuple( std::string("t-") ),
	std::make_tuple( std::string("tt") ),
	std::make_tuple( std::string("test") )
));

TEST_P( CliErrorTest, HandleErrors ) {
  const int argc = 2;
  const char* const argv[argc] = { "program_name", std::get<0>( GetParam() ).c_str() };
  cli::Parser parser;
  ASSERT_THROW( parser.parseArgs( argc, argv ), std::exception );
}

TEST(CliTest, DuplicateFlagErrors) {

  bool flag;
  std::string option;
  cli::Parser parser;
  parser.addFlag( flag, "x", "x_x_x" );
  parser.addOption( option, "y", "y_y_y" );

  ASSERT_THROW( parser.addFlag( flag, "x", "z_z_z" ), std::exception );
  ASSERT_THROW( parser.addFlag( flag, "z", "x_x_x" ), std::exception );
  ASSERT_THROW( parser.addOption( option, "x", "z_z_z" ), std::exception );
  ASSERT_THROW( parser.addOption( option, "z", "x_x_x" ), std::exception );

  ASSERT_THROW( parser.addFlag( flag, "y", "z_z_z" ), std::exception );
  ASSERT_THROW( parser.addFlag( flag, "z", "y_y_y" ), std::exception );
  ASSERT_THROW( parser.addOption( option, "y", "z_z_z" ), std::exception );
  ASSERT_THROW( parser.addOption( option, "z", "y_y_y" ), std::exception );
}


