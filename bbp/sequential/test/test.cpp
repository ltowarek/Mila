#include "gtest/gtest.h"
#include "bbp_sequential.h"

TEST(BBPSequentialTest, Basic) {
    mila::bbp::sequential::BBP bbp;
    EXPECT_EQ(bbp.Run(), 0.0f);
}
