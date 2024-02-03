
#ifndef _LOGGER_MOCK_H_
#define _LOGGER_MOCK_H_

#include <gtest/gtest.h>
#include <logger.h>
#include <logger-sink-stdstream.h>

namespace logger {

class Env : public ::testing::Environment {

public:
  Env();
  ~Env() override;
  void SetUp() override;
  void TearDown() override;

};

} // logger

#endif
