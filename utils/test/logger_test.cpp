#include "gtest/gtest.h"
#include "logger.h"

TEST(PrintfLoggerTest, Critical) {
  auto logger = mila::PrintfLogger();
  printf("\n");
  logger.Critical("Test Critical - %d", 5);
}

TEST(PrintfLoggerTest, Error) {
  auto logger = mila::PrintfLogger();
  printf("\n");
  logger.Error("Test Error - %d", 5);
}

TEST(PrintfLoggerTest, Warning) {
  auto logger = mila::PrintfLogger();
  printf("\n");
  logger.Warning("Test Warning - %d", 5);
}

TEST(PrintfLoggerTest, Info) {
  auto logger = mila::PrintfLogger();
  printf("\n");
  logger.Info("Test Info - %d", 5);
}

TEST(PrintfLoggerTest, Debug) {
  auto logger = mila::PrintfLogger();
  printf("\n");
  logger.Debug("Test Debug - %d", 5);
}
