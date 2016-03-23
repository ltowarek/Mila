#include "gtest/gtest.h"
#include "bbp_parallel.h"

TEST(BBPParallelTest, DefaultConstructor) {
  mila::bbp::parallel::BBP bbp;
  EXPECT_EQ(bbp.precision(), 1e-5f);
  EXPECT_EQ(bbp.platform(), nullptr);
  EXPECT_EQ(bbp.device(), nullptr);
  EXPECT_EQ(bbp.context(), nullptr);
  EXPECT_EQ(bbp.queue(), nullptr);
  EXPECT_EQ(bbp.kernel(), nullptr);
}

TEST(BBPParallelTest, PrecisionConstructor) {
  mila::bbp::parallel::BBP bbp(1e-7f);
  EXPECT_EQ(bbp.precision(), 1e-7f);
  EXPECT_EQ(bbp.platform(), nullptr);
  EXPECT_EQ(bbp.device(), nullptr);
  EXPECT_EQ(bbp.context(), nullptr);
  EXPECT_EQ(bbp.queue(), nullptr);
  EXPECT_EQ(bbp.kernel(), nullptr);
}

TEST(BBPParallelTest, Destructor) {
  // TODO: Add mock objects to this test.
  // Currently GMock cannot be used because the latest builds of GTest do not work on MinGW and FindOpenCL module does not support Cygwin.
  mila::bbp::parallel::BBP bbp;
}

TEST(BBPParallelTest, Initialize) {
  mila::bbp::parallel::BBP bbp;
  bbp.Initialize();
  EXPECT_NE(bbp.platform(), nullptr);
  EXPECT_NE(bbp.device(), nullptr);
  EXPECT_NE(bbp.context(), nullptr);
  EXPECT_NE(bbp.queue(), nullptr);
  EXPECT_NE(bbp.kernel(), nullptr);
}

TEST(BBPParallelTest, ComputeDigits) {
  mila::bbp::parallel::BBP bbp;
  bbp.Initialize();
  EXPECT_EQ(bbp.ComputeDigits(0, 0).size(), 0);
  EXPECT_EQ(bbp.ComputeDigits(1, 0).size(), 1);
  ASSERT_EQ(bbp.ComputeDigits(2, 0).size(), 2);
  EXPECT_NEAR(bbp.ComputeDigits(2, 0)[0], 0.141587316989899f, 1e-5f);
  EXPECT_NEAR(bbp.ComputeDigits(2, 0)[1], 0.265479207038879f, 1e-5f);
  ASSERT_EQ(bbp.ComputeDigits(1, 1).size(), 1);
  EXPECT_NEAR(bbp.ComputeDigits(1, 1)[0], 0.265479207038879f, 1e-5f);
}
