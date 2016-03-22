#include "gtest/gtest.h"
#include "bbp_parallel.h"

TEST(BBPParallelTest, DefaultConstructor) {
  mila::bbp::parallel::BBP bbp;
  EXPECT_EQ(bbp.precision(), 1e-5f);
  EXPECT_EQ(bbp.platform(), nullptr);
  EXPECT_EQ(bbp.device(), nullptr);
  EXPECT_EQ(bbp.context(), nullptr);
  EXPECT_EQ(bbp.queue(), nullptr);
}

TEST(BBPParallelTest, PrecisionConstructor) {
  mila::bbp::parallel::BBP bbp(1e-7f);
  EXPECT_EQ(bbp.precision(), 1e-7f);
  EXPECT_EQ(bbp.platform(), nullptr);
  EXPECT_EQ(bbp.device(), nullptr);
  EXPECT_EQ(bbp.context(), nullptr);
  EXPECT_EQ(bbp.queue(), nullptr);
}

TEST(BBPParallelTest, FullConstructor) {
  // TODO: Update this test with meaningful OpenCL data. GMock cannot be used because the latest builds of
  // GTest do not work on MinGW and FindOpenCL module does not support Cygwin.
  mila::bbp::parallel::BBP bbp(nullptr,
                               nullptr,
                               nullptr,
                               nullptr,
                               1e-7f);
  EXPECT_EQ(bbp.precision(), 1e-7f);
  EXPECT_EQ(bbp.platform(), nullptr);
  EXPECT_EQ(bbp.device(), nullptr);
  EXPECT_EQ(bbp.context(), nullptr);
  EXPECT_EQ(bbp.queue(), nullptr);
}

TEST(BBPParallelTest, Initialize) {
  mila::bbp::parallel::BBP bbp;
  bbp.Initialize();
  EXPECT_EQ(bbp.platform(), nullptr);
  EXPECT_EQ(bbp.device(), nullptr);
  EXPECT_EQ(bbp.context(), nullptr);
  EXPECT_EQ(bbp.queue(), nullptr);
}
