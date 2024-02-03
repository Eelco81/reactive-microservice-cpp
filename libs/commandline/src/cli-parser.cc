
#include "cli-parser.h"
#include <deque>
#include <string>
#include <iostream>

cli::Parser::Parser () = default;

void cli::Parser::parseArgs( int argc, const char * const* argv ) {

  std::deque<std::string> args;
  for ( int i=1; i<argc; i++ ) {
    args.push_back( argv[i] );
  }

  std::vector<std::string> flagShorts;
  std::vector<std::string> flagLongs;
  std::vector<std::pair<std::string, std::string>> optionShorts;
  std::vector<std::pair<std::string, std::string>> optionLongs;
  while ( args.size() > 0 ) {
    auto val = args.front();
    args.pop_front();
    if ( val.size() < 2 ) {
      throw std::exception();
    }
    if ( val[0] != '-' ) {
      throw std::exception();
    }
    val = val.substr( 1, val.size()-1 );
    // short argument
    if ( val[0] != '-' ) {
      if ( val.size() != 1 ) {
        throw std::exception();
      }
      if ( args.size() == 0 || args.front()[0] == '-' ) {
        // must be a flag
        flagShorts.push_back( val );
      }
      else {
        optionShorts.push_back( { val, args.front() } );
        args.pop_front();
      }
    }
    // long argument
    else {
      val = val.substr( 1, val.size()-1 );
      if ( val.size() < 2 ) {
        throw std::exception();
      }
      if ( args.size() == 0 || args.front()[0] == '-' ) {
        // must be a flag
        flagLongs.push_back( val );
      }
      else {
        optionLongs.push_back( { val, args.front() } );
        args.pop_front();
      }
    }
  }

  for ( auto flag : m_flags ) {
    for ( const auto flagVal : flagShorts ) {
      if ( flag.m_short == flagVal ) {
      	flag.m_value = true;
      }
	}
    for ( const auto flagVal : flagLongs ) {
      if ( flag.m_long == flagVal ) {
        flag.m_value = true;
      }
    }
  }

  for ( auto option : m_options ) {
    for ( const auto optVal : optionShorts ) {
      if ( option.m_short == optVal.first ) {
        option.m_value = optVal.second;
      }
	}
    for ( const auto optVal : optionLongs ) {
      if ( option.m_long == optVal.first ) {
        option.m_value = optVal.second;
      }
    }
  }
}

void cli::Parser::addFlag( bool& flag, const std::string& shortFlag, const std::string& longFlag ) {

  for (const auto flag : m_flags) {
	if ( flag.m_short == shortFlag || flag.m_long == longFlag ) {
	  throw std::exception();
	}
  }
  for (const auto option : m_options) {
	if ( option.m_short == shortFlag || option.m_long == longFlag ) {
	  throw std::exception();
	}
  }

  Flag obj{ flag, shortFlag, longFlag };
  m_flags.push_back( obj );
}


void cli::Parser::addOption( std::string& variable, const std::string& shortFlag, const std::string& longFlag, OptionType optionType ) {

  for (const auto flag : m_flags) {
    if ( flag.m_short == shortFlag || flag.m_long == longFlag ) {
      throw std::exception();
    }
  }
  for (const auto option : m_options) {
    if ( option.m_short == shortFlag || option.m_long == longFlag ) {
      throw std::exception();
    }
  }

  Option obj{ variable, shortFlag, longFlag };
  m_options.push_back( obj );
}
