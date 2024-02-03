
#include <iostream>
#include "logger-mock.h"

logger::Env::Env() = default;
logger::Env::~Env() = default;

void logger::Env::SetUp() {
  logger::Logger::get().addSink( std::shared_ptr<logger::SinkIf>( new logger::StdStreamSink() ) );
  logger::Logger::get().setLevel( logger::lTRACE );
}

void logger::Env::TearDown() {
  logger::Logger::get().clearSinks();
}
