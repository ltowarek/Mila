#include "gtest/gtest.h"
#include "n_body_utils.h"

TEST(NBodyUtilsTest, GenerateRandomValue) {
  for (int i = 0; i < 10; ++i) {
    float value = mila::GenerateRandomValue(1.0f, 2.0f);
    EXPECT_GE(value, 1.0f);
    EXPECT_LT(value, 2.0f);
  }
}
