#include "gtest/gtest.h"
#include "bbp_sequential.h"

TEST(BBPSequentialTest, FloatPrecision) {
  EXPECT_EQ(static_cast<size_t>(powf(8 * 100 + 6, 2)), 649636);
  EXPECT_EQ(static_cast<size_t>(powf(8 * 1000 + 6, 2)), 64096036);
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
  EXPECT_NEAR(bbp.ComputeDigits(2, 0)[0], 0.141587316989899f, 1e-5);
  EXPECT_NEAR(bbp.ComputeDigits(2, 0)[1], 0.265479207038879f, 1e-5);
  ASSERT_EQ(bbp.ComputeDigits(1, 1).size(), 1);
  EXPECT_NEAR(bbp.ComputeDigits(1, 1)[0], 0.265479207038879f, 1e-5);
}

TEST(BBPSequentialTest, ComputeDigit) {
  mila::bbp::sequential::BBP bbp;
  EXPECT_NEAR(bbp.ComputeDigit(0), 0.141587316989899f, 1e-5);
  EXPECT_NEAR(bbp.ComputeDigit(1), 0.265479207038879f, 1e-5);
  EXPECT_NEAR(bbp.ComputeDigit(1000), 1.7962465286254883f, 1e-5);
}

TEST(BBPSequentialTest, ConvertFractionToHex) {
  mila::bbp::sequential::BBP bbp;
  EXPECT_EQ(bbp.ConvertFractionToHex(0.141587316989899f, 6), "243F11");
  EXPECT_EQ(bbp.ConvertFractionToHex(0.265479207038879f, 6), "43F672");
  EXPECT_EQ(bbp.ConvertFractionToHex(0.7426779270172f, 6), "BE2024");
  EXPECT_EQ(bbp.ConvertFractionToHex(0.0f, 0), "");
  EXPECT_EQ(bbp.ConvertFractionToHex(1.0f, 1), "0");
  EXPECT_EQ(bbp.ConvertFractionToHex(1.0f, 2), "00");
  EXPECT_EQ(bbp.ConvertFractionToHex(2.0f, 1), "0");
  EXPECT_EQ(bbp.ConvertFractionToHex(1.1f, 1), "1");
  EXPECT_EQ(bbp.ConvertFractionToHex(1.2f, 1), "3");
  EXPECT_EQ(bbp.ConvertFractionToHex(1.3f, 1), "4");
  EXPECT_EQ(bbp.ConvertFractionToHex(1.4f, 1), "6");
  EXPECT_EQ(bbp.ConvertFractionToHex(1.5f, 1), "8");
  EXPECT_EQ(bbp.ConvertFractionToHex(1.6f, 1), "9");
  EXPECT_EQ(bbp.ConvertFractionToHex(1.7f, 1), "B");
  EXPECT_EQ(bbp.ConvertFractionToHex(1.8f, 1), "C");
  EXPECT_EQ(bbp.ConvertFractionToHex(1.9f, 1), "E");
}

TEST(BBPSequentialTest, ConvertFractionsToHex) {
  mila::bbp::sequential::BBP bbp;
  std::vector<float> fractions = {0.141587316989899f, 0.265479207038879f};
  ASSERT_EQ(bbp.ConvertFractionsToHex(fractions, 6).size(), fractions.size());
  EXPECT_EQ(bbp.ConvertFractionsToHex(fractions, 6)[0], "243F11");
  EXPECT_EQ(bbp.ConvertFractionsToHex(fractions, 6)[1], "43F672");
}

TEST(BBPSequentialTest, Series) {
  mila::bbp::sequential::BBP bbp;
  EXPECT_NEAR(bbp.Series(1, 1000), 0.93149524927139282f, 1e-5);
  EXPECT_NEAR(bbp.Series(4, 1000), 0.36730793118476868f, 1e-5);
  EXPECT_NEAR(bbp.Series(5, 1000), 0.70736938714981079f, 1e-5);
  EXPECT_NEAR(bbp.Series(6, 1000), 0.48774918913841248f, 1e-5);
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
