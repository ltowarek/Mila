#include "gtest/gtest.h"
#include "bbp_sequential.h"

TEST(BBPSequentialTest, Run) {
    mila::bbp::sequential::BBP bbp;
    EXPECT_EQ(bbp.Run(), 0.0f);
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
