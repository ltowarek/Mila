#include "gtest/gtest.h"
#include "bbp_parallel.h"

TEST(BBPParallelTest, DefaultConstructor) {
  mila::bbp::parallel::BBP bbp;
  EXPECT_EQ(bbp.precision(), 1e-5);
}

