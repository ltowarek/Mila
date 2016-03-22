#include "gtest/gtest.h"
#include <cmath>

TEST(BBPParallelTest, FloatPrecision) {
  EXPECT_EQ(static_cast<size_t>(powf(8 * 100 + 6, 2)), 649636);
  EXPECT_EQ(static_cast<size_t>(powf(8 * 1000 + 6, 2)), 64096036);
}
