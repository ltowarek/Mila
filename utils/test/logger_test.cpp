#include "gtest/gtest.h"
#include "logger.hpp"

class PrintfLoggerTest : public testing::Test {
 protected:
  virtual void SetUp() {
    logger_ = mila::PrintfLogger();
    logger_.SetLevel(mila::LEVELS::DEBUG);
    printf("\n");
  }
  mila::PrintfLogger logger_;
};

TEST_F(PrintfLoggerTest, Critical) {
  this->logger_.Critical("Test Critical - %d", 5);
}

TEST_F(PrintfLoggerTest, Error) {
  this->logger_.Error("Test Error - %d", 5);
}

TEST_F(PrintfLoggerTest, Warning) {
  this->logger_.Warning("Test Warning - %d", 5);
}

TEST_F(PrintfLoggerTest, Info) {
  this->logger_.Info("Test Info - %d", 5);
}

TEST_F(PrintfLoggerTest, Debug) {
  this->logger_.Debug("Test Debug - %d", 5);
}

TEST_F(PrintfLoggerTest, Levels) {
  this->logger_.SetLevel(mila::LEVELS::CRITICAL);
  this->logger_.Debug("Critical level");
  this->logger_.Critical("Critical level");
}
