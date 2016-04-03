#include "gtest/gtest.h"
#include "mean_shift_parallel.h"

TEST(BBPParallelTest, DefaultConstructor) {
  mila::meanshift::parallel::MeanShift mean_shift;
  EXPECT_EQ(mean_shift.precision(), 1e-5f);
  EXPECT_EQ(mean_shift.max_iterations(), 100);
  EXPECT_EQ(mean_shift.platform_id(), 0);
  EXPECT_EQ(mean_shift.device_id(), 0);
}

TEST(MeanShiftParallelTest, DeviceTypeConstructor) {
  mila::meanshift::parallel::MeanShift mean_shift_0_0(0, 0);
  EXPECT_EQ(mean_shift_0_0.platform_id(), 0);
  EXPECT_EQ(mean_shift_0_0.device_id(), 0);
  EXPECT_EQ(mean_shift_0_0.precision(), 1e-5f);
  EXPECT_EQ(mean_shift_0_0.max_iterations(), 100);
  mila::meanshift::parallel::MeanShift mean_shift_1_0(1, 0);
  EXPECT_EQ(mean_shift_1_0.platform_id(), 1);
  EXPECT_EQ(mean_shift_1_0.device_id(), 0);
  EXPECT_EQ(mean_shift_1_0.precision(), 1e-5f);
  EXPECT_EQ(mean_shift_1_0.max_iterations(), 100);
  mila::meanshift::parallel::MeanShift mean_shift_0_1(0, 1);
  EXPECT_EQ(mean_shift_0_1.platform_id(), 0);
  EXPECT_EQ(mean_shift_0_1.device_id(), 1);
  EXPECT_EQ(mean_shift_0_1.precision(), 1e-5f);
  EXPECT_EQ(mean_shift_0_1.max_iterations(), 100);
}

TEST(MeanShiftParallelTest, Constructor) {
  mila::meanshift::parallel::MeanShift mean_shift(1, 1, 1e-7f, 123);
  EXPECT_EQ(mean_shift.precision(), 1e-7f);
  EXPECT_EQ(mean_shift.max_iterations(), 123);
  EXPECT_EQ(mean_shift.platform_id(), 1);
  EXPECT_EQ(mean_shift.device_id(), 1);
}
