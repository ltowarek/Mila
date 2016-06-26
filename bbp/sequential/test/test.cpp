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

TEST(BBPSequentialTest, DefaultConstructor) {
  mila::bbp::sequential::BBP bbp;
  EXPECT_EQ(bbp.precision(), 1e-5f);
}

TEST(BBPSequentialTest, Constructor) {
  mila::bbp::sequential::BBP bbp(1e-7f);
  EXPECT_EQ(bbp.precision(), 1e-7f);
}

TEST(BBPSequentialTest, Run) {
  mila::bbp::sequential::BBP bbp;
  EXPECT_EQ(bbp.Run(0, 0), "");
  EXPECT_EQ(bbp.Run(1, 0), "2");
  EXPECT_EQ(bbp.Run(2, 0), "24");
  EXPECT_EQ(bbp.Run(3, 0), "243");
  EXPECT_EQ(bbp.Run(4, 0), "243F");
  EXPECT_EQ(bbp.Run(5, 0), "243F6");
  EXPECT_EQ(bbp.Run(540, 0), "243F6A8885A308D313198A2E03707344A4093822299F31D0082EFA98EC4E6C89452821E638D01377BE5466"
      "CF34E90C6CC0AC29B7C97C50DD3F84D5B5B54709179216D5D98979FB1BD1310BA698DFB5AC2FFD72DBD01A"
      "DFB7B8E1AFED6A267E96BA7C9045F12C7F9924A19947B3916CF70801F2E2858EFC16636920D871574E69A4"
      "58FEA3F4933D7E0D95748F728EB658718BCD5882154AEE7B54A41DC25A59B59C30D5392AF26013C5D1B023"
      "286085F0CA417918B8DB38EF8E79DCB0603A180E6C9E0E8BB01E8A3ED71577C1BD314B2778AF2FDA55605C"
      "60E65525F3AA55AB945748986263E8144055CA396A2AAB10B6B4CC5C341141E8CEA15486AF7C72E993B3EE"
      "1411636FBC2A2BA9C55D7418");
  EXPECT_EQ(bbp.Run(24, 516), "1411636FBC2A2BA9C55D7418");
}

TEST(BBPSequentialTest, ComputeDigits) {
  mila::bbp::sequential::BBP bbp;
  EXPECT_EQ(bbp.ComputeDigits(0, 0).size(), 0);
  EXPECT_EQ(bbp.ComputeDigits(1, 0).size(), 1);
  ASSERT_EQ(bbp.ComputeDigits(2, 0).size(), 2);
  EXPECT_NEAR(bbp.ComputeDigits(2, 0)[0], 0.141587316989899f, 1e-5f);
  EXPECT_NEAR(bbp.ComputeDigits(2, 0)[1], 0.265479207038879f, 1e-5f);
  ASSERT_EQ(bbp.ComputeDigits(1, 1).size(), 1);
  EXPECT_NEAR(bbp.ComputeDigits(1, 1)[0], 0.265479207038879f, 1e-5f);
}

TEST(BBPSequentialTest, ComputeDigit) {
  mila::bbp::sequential::BBP bbp;
  EXPECT_NEAR(bbp.ComputeDigit(0), 0.141587316989899f, 1e-5f);
  EXPECT_NEAR(bbp.ComputeDigit(1), 0.265479207038879f, 1e-5f);
  EXPECT_NEAR(bbp.ComputeDigit(1000), 1.7962465286254883f, 1e-5f);
}

TEST(BBPSequentialTest, Series) {
  mila::bbp::sequential::BBP bbp;
  EXPECT_NEAR(bbp.Series(1, 1000), 0.93149524927139282f, 1e-5f);
  EXPECT_NEAR(bbp.Series(4, 1000), 0.36730793118476868f, 1e-5f);
  EXPECT_NEAR(bbp.Series(5, 1000), 0.70736938714981079f, 1e-5f);
  EXPECT_NEAR(bbp.Series(6, 1000), 0.48774918913841248f, 1e-5f);
}

TEST(BBPSequentialTest, LargestPowerOfTwoLessOrEqual) {
  mila::bbp::sequential::BBP bbp;
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
  mila::bbp::sequential::BBP bbp;
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

TEST(BBPSequentialProfilerTest, DefaultConstructor) {
  mila::bbp::sequential::BBPProfiler bbp;
  EXPECT_EQ(bbp.precision(), 1e-5f);
  EXPECT_EQ(bbp.main_result(), "Run");
}

TEST(BBPSequentialProfilerTest, Constructor) {
  mila::bbp::sequential::BBPProfiler bbp(1e-7f);
  EXPECT_EQ(bbp.precision(), 1e-7f);
  EXPECT_EQ(bbp.main_result(), "Run");
}

TEST(BBPSequentialProfilerTest, Run) {
  mila::bbp::sequential::BBPProfiler bbp;
  EXPECT_EQ(bbp.Run(0, 0), "");
  EXPECT_EQ(bbp.Run(1, 0), "2");
  EXPECT_EQ(bbp.Run(2, 0), "24");
  EXPECT_EQ(bbp.Run(3, 0), "243");
  EXPECT_EQ(bbp.Run(4, 0), "243F");
  EXPECT_EQ(bbp.Run(5, 0), "243F6");
  EXPECT_EQ(bbp.Run(540, 0), "243F6A8885A308D313198A2E03707344A4093822299F31D0082EFA98EC4E6C89452821E638D01377BE5466"
      "CF34E90C6CC0AC29B7C97C50DD3F84D5B5B54709179216D5D98979FB1BD1310BA698DFB5AC2FFD72DBD01A"
      "DFB7B8E1AFED6A267E96BA7C9045F12C7F9924A19947B3916CF70801F2E2858EFC16636920D871574E69A4"
      "58FEA3F4933D7E0D95748F728EB658718BCD5882154AEE7B54A41DC25A59B59C30D5392AF26013C5D1B023"
      "286085F0CA417918B8DB38EF8E79DCB0603A180E6C9E0E8BB01E8A3ED71577C1BD314B2778AF2FDA55605C"
      "60E65525F3AA55AB945748986263E8144055CA396A2AAB10B6B4CC5C341141E8CEA15486AF7C72E993B3EE"
      "1411636FBC2A2BA9C55D7418");
  EXPECT_EQ(bbp.Run(24, 516), "1411636FBC2A2BA9C55D7418");
}

TEST(BBPSequentialProfilerTest, RunWithProfiling) {
  mila::bbp::sequential::BBPProfiler bbp;
  EXPECT_EQ(bbp.results().count("Run"), 0);
  EXPECT_EQ(bbp.Run(24, 516), "1411636FBC2A2BA9C55D7418");
  EXPECT_EQ(bbp.results().count("Run"), 1);
}
