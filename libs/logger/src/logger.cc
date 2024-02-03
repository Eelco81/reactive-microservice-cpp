
#include <chrono>
#include <string>
#include "logger.h"

void logger::Logger::log( const Message& message ) {
  if ( message.m_level <= m_level ) {
    for ( auto sink : m_sinks ) {
      sink->log( message );
    }
  }
}

void logger::Logger::addSink( const std::shared_ptr<SinkIf>& sink ) {
  m_sinks.push_back( sink );
}

void logger::Logger::clearSinks() {
  m_sinks.clear();
}

void logger::Logger::setLevel( Level level ) {
  m_level = level;
}


