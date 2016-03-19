#include "gtest/gtest.h"
#include "bbp_sequential.h"


TEST(BBPSequentialTest, DefaultConstructor) {
    mila::bbp::sequential::BBP bbp;
    EXPECT_EQ(bbp.precision(), 1e-5);
}

TEST(BBPSequentialTest, Constructor) {
    mila::bbp::sequential::BBP bbp(1e-7);
    EXPECT_EQ(bbp.precision(), 1e-7);
}

TEST(BBPSequentialTest, Run) {
    mila::bbp::sequential::BBP bbp;
    EXPECT_NEAR(bbp.Run(0), 0.141587316989899f, 1e-5);
    EXPECT_NEAR(bbp.Run(1), 0.265479207038879f, 1e-5);
    EXPECT_NEAR(bbp.Run(100000), 0.7426779270172f, 1e-5);
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

TEST(BBPSequentialTest, Series) {
    mila::bbp::sequential::BBP bbp;
    EXPECT_NEAR(bbp.Series(1, 100000), 0.298238158f, 1e-5);
    EXPECT_NEAR(bbp.Series(4, 100000), 0.8211689f, 1e-5);
    EXPECT_NEAR(bbp.Series(5, 100000), 0.147965193f, 1e-5);
    EXPECT_NEAR(bbp.Series(6, 100000), 0.659971654f, 1e-5);
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
