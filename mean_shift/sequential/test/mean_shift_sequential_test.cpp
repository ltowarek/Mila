#include "gtest/gtest.h"
#include "mean_shift_sequential.h"
#include "mean_shift_sequential_profiler.h"

TEST(SequentialMeanShiftTest, DistanceZero) {
  const auto mean_shift = mila::SequentialMeanShift(nullptr);
  const auto point1 = mila::Point{0.0f};
  const auto point2 = mila::Point{0.0f};
  EXPECT_EQ(mean_shift.Distance(point1, point2), 0.0f);
}

TEST(SequentialMeanShiftTest, DistanceComplex) {
  const auto mean_shift = mila::SequentialMeanShift(nullptr);
  const auto point1 = mila::Point{-7.0f, -4.0f, 3.0f, 0.0f};
  const auto point2 = mila::Point {17.0f, 6.0f, 2.5f, 0.0f};
  EXPECT_NEAR(mean_shift.Distance(point1, point2), 26.00480f, 1e-5f);
}

TEST(SequentialMeanShiftTest, GaussianKernelZero) {
  const auto mean_shift = mila::SequentialMeanShift(nullptr);
  const auto x = 0.0f;
  const auto sigma = 1.0f;
  EXPECT_NEAR(mean_shift.GaussianKernel(x, sigma), 0.39894f, 1e-5f);
}

TEST(SequentialMeanShiftTest, GaussianKernelUndefined) {
  const auto mean_shift = mila::SequentialMeanShift(nullptr);
  const auto x = 0.0f;
  const auto sigma = 0.0f;
  EXPECT_NEAR(mean_shift.GaussianKernel(x, sigma), 0.0f, 1e-5f);
}

TEST(SequentialMeanShiftTest, GaussianKernelComplex) {
  const auto mean_shift = mila::SequentialMeanShift(nullptr);
  const auto x = 2.25f;
  const auto sigma = 2.0f;
  EXPECT_NEAR(mean_shift.GaussianKernel(x, sigma), 0.10593f, 1e-5f);
}

TEST(SequentialMeanShiftTest, ShiftPointZero) {
  const auto mean_shift = mila::SequentialMeanShift(nullptr);
  const auto point = mila::Point{0.0f};
  const auto points = std::vector<mila::Point>{{1.0f}, {-1.0f}};
  const auto bandwidth = 1.0f;

  const auto output = mean_shift.ShiftPoint(point, points, bandwidth);

  EXPECT_NEAR(output.x, 0.0f, 1e-5f);
  EXPECT_NEAR(output.y, 0.0f, 1e-5f);
  EXPECT_NEAR(output.z, 0.0f, 1e-5f);
  EXPECT_NEAR(output.w, 0.0f, 1e-5f);
}

TEST(SequentialMeanShiftTest, ShiftPointUndefined) {
  const auto mean_shift = mila::SequentialMeanShift(nullptr);
  const auto point = mila::Point{0.0f};
  const auto points = std::vector<mila::Point>{{1.0f}, {-1.0f}};
  const auto bandwidth = 0.0f;

  const auto output = mean_shift.ShiftPoint(point, points, bandwidth);

  EXPECT_NEAR(output.x, 0.0f, 1e-5f);
  EXPECT_NEAR(output.y, 0.0f, 1e-5f);
  EXPECT_NEAR(output.z, 0.0f, 1e-5f);
  EXPECT_NEAR(output.w, 0.0f, 1e-5f);
}

TEST(SequentialMeanShiftTest, ShiftPointSimple) {
  const auto mean_shift = mila::SequentialMeanShift(nullptr);
  const auto point = mila::Point{0.0f};
  const auto points = std::vector<mila::Point>{{1.0f, 1.0f, 0.0f, 0.0f}, {-2.0f, -2.0f, 0.0f, 0.0f}};
  const auto bandwidth = 2.0f;

  const auto output = mean_shift.ShiftPoint(point, points, bandwidth);

  EXPECT_NEAR(output.x, 0.037536f, 1e-5f);
  EXPECT_NEAR(output.y, 0.037536f, 1e-5f);
  EXPECT_NEAR(output.z, 0.0f, 1e-5f);
  EXPECT_NEAR(output.w, 0.0f, 1e-5f);
}

TEST(SequentialMeanShiftTest, ShiftPointComplex) {
  const auto mean_shift = mila::SequentialMeanShift(nullptr);
  const auto point = mila::Point{1.0f, -5.0f, 8.0f, 0.0f};
  const auto points =
      std::vector<mila::Point>{{1.5f, 1.0f, -10.0f, 0.0f}, {-2.0f, 20.0f, -1.25f, 0.0f}, {5.5f, 7.3f, -8.75f, 0.0f}};
  const auto bandwidth = 2.0f;

  const auto output = mean_shift.ShiftPoint(point, points, bandwidth);

  EXPECT_NEAR(output.x, 1.50004f, 1e-5f);
  EXPECT_NEAR(output.y, 1.00006f, 1e-5f);
  EXPECT_NEAR(output.z, -9.99998f, 1e-5f);
  EXPECT_NEAR(output.w, 0.0f, 1e-5f);
}

TEST(SequentialMeanShiftProfilerTest, RunWithProfiling) {
  mila::SequentialMeanShiftProfiler mean_shift;

  const auto points = std::vector<mila::Point>{{0.0f, 1.0f, 0.0f, 0.0f},
                                               {2.0f, 3.0f, 0.0f, 0.0f},
                                               {10.0f, 11.0f, 0.0f, 0.0f},
                                               {12.0f, 13.0f, 0.0f, 0.0f}
  };
  const auto bandwidth = 3.0f;

  EXPECT_EQ(mean_shift.results().count("Points per second"), 0);
  EXPECT_EQ(mean_shift.results().count("Run"), 0);

  mean_shift.Run(points, bandwidth);

  EXPECT_EQ(mean_shift.results().count("Points per second"), 1);
  EXPECT_EQ(mean_shift.results().count("Run"), 1);
}
