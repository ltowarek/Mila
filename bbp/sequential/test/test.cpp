#include "gtest/gtest.h"
#include "bbp_sequential.h"

TEST(BBPSequentialTest, Run) {
    mila::bbp::sequential::BBP bbp;
    EXPECT_EQ(bbp.Run(), 0.0f);
}

TEST(BBPSequentialTest, Series) {
    mila::bbp::sequential::BBP bbp;
    size_t d = 1;
    size_t j = 1;
    EXPECT_EQ(bbp.Series(j, d), 0.0f);
}
