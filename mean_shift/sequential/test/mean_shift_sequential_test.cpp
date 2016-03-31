#include "gtest/gtest.h"
#include "mean_shift_sequential.h"

TEST(MeanShiftPointTest, InitializeWithSingleValue) {
  mila::meanshift::sequential::Point point = {0.0f};
  EXPECT_EQ(point.x, 0.0f);
  EXPECT_EQ(point.y, 0.0f);
  EXPECT_EQ(point.z, 0.0f);
  EXPECT_EQ(point.w, 0.0f);
}

TEST(MeanShiftPointTest, InitializeWithMultipleValues) {
  mila::meanshift::sequential::Point point = {1.0f, 2.0f, 3.0f, 4.0f};
  EXPECT_EQ(point.x, 1.0f);
  EXPECT_EQ(point.y, 2.0f);
  EXPECT_EQ(point.z, 3.0f);
  EXPECT_EQ(point.w, 4.0f);
}

TEST(MeanShiftSequentialTest, DistanceZero) {
  mila::meanshift::sequential::Point point1 = {0.0f};
  mila::meanshift::sequential::Point point2 = {0.0f};
  EXPECT_EQ(mila::meanshift::sequential::Distance(point1, point2), 0.0f);
}

TEST(MeanShiftSequentialTest, DistanceComplex) {
  mila::meanshift::sequential::Point point1 = {-7.0f, -4.0f, 3.0f, 0.0f};
  mila::meanshift::sequential::Point point2 = {17.0f, 6.0f, 2.5f, 0.0f};
  EXPECT_NEAR(mila::meanshift::sequential::Distance(point1, point2), 26.00480f, 1e-5f);
}
