
#ifndef _CLI_PARSER_H_
#define _CLI_PARSER_H_

#include <memory>
#include <vector>
#include <cstdint>
#include <string>

namespace cli {

enum OptionType {
  OPTIONAL = 0,
  REQUIRED = 1
};

class Parser {
public:
  Parser();
  void parseArgs(  int argc, const char* const* argv );

  void addFlag( bool& flag, const std::string& shortFlag, const std::string& longFlag );
  void addOption( std::string& variable, const std::string& shortFlag, const std::string& longFlag, OptionType optionType = OPTIONAL );

private:

  struct Flag {
    bool& m_value;
    std::string m_short;
    std::string m_long;
  };

  struct Option {
    std::string& m_value;
    std::string m_short;
    std::string m_long;
  };


  std::vector<Flag> m_flags;
  std::vector<Option> m_options;

};

} // cli

#endif
