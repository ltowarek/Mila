#include "gtest/gtest.h"
#include "bbp_sequential.h"
#include "bbp_sequential_profiler.h"

TEST(BBPSequentialTest, FloatPrecision) {
  EXPECT_NEAR(powf(8 * 100 + 6, 2), 649636, 1e-5);
  EXPECT_NEAR(powf(8 * 1000 + 6, 2), 64096036, 1e-5);
  EXPECT_NEAR(pow(8 * 10000 + 6, 2), 6400960036, 1e-5);
  EXPECT_NEAR(pow(8 * 100000 + 6, 2), 640009600036, 1e-5);
  EXPECT_NEAR(pow(8 * 1000000 + 6, 2), 64000096000036, 1e-5);
  EXPECT_NEAR(pow(8 * 10000000 + 6, 2), 6400000960000036, 1e-5);
  EXPECT_NEAR(pow(8 * 100000000 + 6, 2), 640000009600000036, 1e-5);
}

TEST(BBPSequentialTest, ComputeDigit) {
  mila::SequentialBBP bbp(nullptr);
  EXPECT_NEAR(bbp.ComputeDigit(0), 0.141587316989899f, 1e-5f);
  EXPECT_NEAR(bbp.ComputeDigit(1), 0.265479207038879f, 1e-5f);
  EXPECT_NEAR(bbp.ComputeDigit(1000), 1.7962465286254883f, 1e-5f);
}

TEST(BBPSequentialTest, Series) {
  mila::SequentialBBP bbp(nullptr);
  EXPECT_NEAR(bbp.Series(1, 1000), 0.93149524927139282f, 1e-5f);
  EXPECT_NEAR(bbp.Series(4, 1000), 0.36730793118476868f, 1e-5f);
  EXPECT_NEAR(bbp.Series(5, 1000), 0.70736938714981079f, 1e-5f);
  EXPECT_NEAR(bbp.Series(6, 1000), 0.48774918913841248f, 1e-5f);
}

TEST(BBPSequentialTest, LargestPowerOfTwoLessOrEqual) {
  mila::SequentialBBP bbp(nullptr);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(0), 0);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(1), 1);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(2), 2);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(3), 2);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(4), 3);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(5), 3);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(10), 4);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(100), 7);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(1000), 10);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(33554432), 26);
}

TEST(BBPSequentialTest, ModularExponentiation) {
  mila::SequentialBBP bbp(nullptr);
  EXPECT_EQ(bbp.ModularExponentiation(0.0f, 0, 0.0f), 1.0f);
  EXPECT_EQ(bbp.ModularExponentiation(0.0f, 0, 1.0f), 0.0f);
  EXPECT_EQ(bbp.ModularExponentiation(16.0f, 0, 1.0f), 0.0f);
  EXPECT_EQ(bbp.ModularExponentiation(16.0f, 1, 1.0f), 0.0f);
  EXPECT_EQ(bbp.ModularExponentiation(16.0f, 5, 1.0f), 0.0f);
  EXPECT_EQ(bbp.ModularExponentiation(16.0f, 16, 16.0f), 0.0f);
  EXPECT_EQ(bbp.ModularExponentiation(16.0f, 2, 7.0f), 4.0f);
  EXPECT_EQ(bbp.ModularExponentiation(5.0f, 3, 13.0f), 8.0f);
  EXPECT_EQ(bbp.ModularExponentiation(8.5f, 2, 3.25f), 0.75f);
  EXPECT_EQ(bbp.ModularExponentiation(16.0f, 999985, 121.0f), 56.0f);
}

TEST(BBPSequentialProfilerTest, RunWithProfiling) {
  mila::SequentialBBPProfiler bbp(nullptr);
  EXPECT_EQ(bbp.results().count("Run"), 0);
  EXPECT_EQ(bbp.results().count("Digits per second"), 0);
  EXPECT_EQ(bbp.Run(24, 516), "1411636FBC2A2BA9C55D7418");
  EXPECT_EQ(bbp.results().count("Run"), 1);
  EXPECT_EQ(bbp.results().count("Digits per second"), 1);
}

