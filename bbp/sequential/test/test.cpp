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
    EXPECT_EQ(bbp.Run(), 0.0f);
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
