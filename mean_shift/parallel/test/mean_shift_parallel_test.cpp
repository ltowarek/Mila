#include "gtest/gtest.h"
#include "mean_shift_parallel.h"

TEST(MeanShiftPointTest, ConvertVectorToPoints) {
  std::vector<uint8_t> data = {1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<cl_float4> expected_output = {{1.0f, 2.0f, 3.0f, 4.0f},
                                            {5.0f, 6.0f, 7.0f, 8.0f}
  };

  std::vector<cl_float4> output = mila::meanshift::parallel::ConvertVectorToPoints(data);

  for (size_t i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(output[i].x, expected_output[i].x);
    EXPECT_EQ(output[i].y, expected_output[i].y);
    EXPECT_EQ(output[i].z, expected_output[i].z);
    EXPECT_EQ(output[i].w, expected_output[i].w);
  }
}

TEST(MeanShiftPointTest, ConvertVectorToPointsIllegal) {
  std::vector<uint8_t> data = {1, 2, 3};

  std::vector<cl_float4> output = mila::meanshift::parallel::ConvertVectorToPoints(data);

  EXPECT_EQ(output.size(), 0);
}

TEST(MeanShiftPointTest, ConvertPointsToVector) {
  std::vector<cl_float4> data = {{1.0f, 2.0f, 3.0f, 4.0f},
                                 {5.0f, 6.0f, 7.0f, 8.0f}
  };
  std::vector<uint8_t> expected_output = {1, 2, 3, 4, 5, 6, 7, 8};

  std::vector<uint8_t> output = mila::meanshift::parallel::ConvertPointsToVector(data);

  for (size_t i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(output[i], expected_output[i]);
  }
}

TEST(MeanShiftParallelTest, DefaultConstructor) {
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
