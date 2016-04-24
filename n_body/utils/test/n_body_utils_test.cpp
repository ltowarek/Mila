#include "gtest/gtest.h"
#include "n_body_utils.h"

TEST(NBodyUtilsTest, GenerateRandomValue) {
  for (int i = 0; i < 10; ++i) {
    int value = mila::nbody::utils::GenerateRandomValue(1, 2);
    EXPECT_GE(value, 1);
    EXPECT_LE(value, 2);
  }
}
