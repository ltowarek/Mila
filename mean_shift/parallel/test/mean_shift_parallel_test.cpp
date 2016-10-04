#include "gtest/gtest.h"
#include "mean_shift_parallel.h"
#include "mean_shift_parallel_profiler.h"

TEST(MeanShiftParallelProfilerTest, InitializeWithProfiling) {
  mila::ParallelMeanShiftProfiler mean_shift;
  EXPECT_EQ(mean_shift.results().count("Initialize"), 0);
  mean_shift.Initialize();
  EXPECT_EQ(mean_shift.results().count("Initialize"), 1);
}

TEST(MeanShiftParallelProfilerTest, RunWithProfiling) {
  mila::ParallelMeanShiftProfiler mean_shift;

  std::vector<mila::Point> points = {{0.0f, 1.0f, 0.0f, 0.0f},
                                   {2.0f, 3.0f, 0.0f, 0.0f},
                                   {10.0f, 11.0f, 0.0f, 0.0f},
                                   {12.0f, 13.0f, 0.0f, 0.0f}
  };
  float bandwidth = 3.0f;

  EXPECT_EQ(mean_shift.results().count("Run"), 0);
  EXPECT_EQ(mean_shift.results().count("Points per second"), 0);
  mean_shift.Run(points, bandwidth);
  EXPECT_EQ(mean_shift.results().count("Run"), 1);
  EXPECT_EQ(mean_shift.results().count("Points per second"), 1);
}

TEST(MeanShiftParallelProfilerTest, GetBuildKernelAsMicroseconds) {
  mila::ParallelMeanShiftProfiler mean_shift;
  mean_shift.Initialize();
  EXPECT_GT(mean_shift.GetBuildKernelAsMicroseconds(), 0);
}

TEST(MeanShiftParallelProfilerTest, GetCopyBufferAsMicroseconds) {
  std::vector<mila::Point> points = {{0.0f, 1.0f, 0.0f, 0.0f},
                                   {2.0f, 3.0f, 0.0f, 0.0f},
                                   {10.0f, 11.0f, 0.0f, 0.0f},
                                   {12.0f, 13.0f, 0.0f, 0.0f}
  };
  float bandwidth = 3.0f;

  mila::ParallelMeanShiftProfiler mean_shift;
  mean_shift.Run(points, bandwidth);
  EXPECT_GT(mean_shift.GetCopyBufferAsMicroseconds(), 0);
}

TEST(MeanShiftParallelProfilerTest, GetReadBufferAsMicroseconds) {
  std::vector<mila::Point> points = {{0.0f, 1.0f, 0.0f, 0.0f},
                                   {2.0f, 3.0f, 0.0f, 0.0f},
                                   {10.0f, 11.0f, 0.0f, 0.0f},
                                   {12.0f, 13.0f, 0.0f, 0.0f}
  };
  float bandwidth = 3.0f;

  mila::ParallelMeanShiftProfiler mean_shift;
  mean_shift.Run(points, bandwidth);
  EXPECT_GT(mean_shift.GetReadBufferAsMicroseconds(), 0);
}

TEST(MeanShiftParallelProfilerTest, GetEnqueueNDRangeAsMicroseconds) {
  std::vector<mila::Point> points = {{0.0f, 1.0f, 0.0f, 0.0f},
                                   {2.0f, 3.0f, 0.0f, 0.0f},
                                   {10.0f, 11.0f, 0.0f, 0.0f},
                                   {12.0f, 13.0f, 0.0f, 0.0f}
  };
  float bandwidth = 3.0f;

  mila::ParallelMeanShiftProfiler mean_shift;
  mean_shift.Run(points, bandwidth);
  EXPECT_GT(mean_shift.GetEnqueueNDRangeAsMicroseconds(), 0);
}

TEST(MeanShiftParallelProfilerTest, GetOpenCLStatisticsAsString) {
  mila::ParallelMeanShiftProfiler mean_shift;
  EXPECT_STREQ("", mean_shift.GetOpenCLStatisticsAsString().c_str());
}

TEST(MeanShiftParallelProfilerTest, GetOpenCLStatisticsAsStringWithRun) {
  std::vector<mila::Point> points = {{0.0f, 1.0f, 0.0f, 0.0f},
                                   {2.0f, 3.0f, 0.0f, 0.0f},
                                   {10.0f, 11.0f, 0.0f, 0.0f},
                                   {12.0f, 13.0f, 0.0f, 0.0f}
  };
  float bandwidth = 3.0f;

  mila::ParallelMeanShiftProfiler mean_shift;
  mean_shift.Run(points, bandwidth);
  EXPECT_STRNE("", mean_shift.GetOpenCLStatisticsAsString().c_str());
}

TEST(MeanShiftParallelProfilerTest, GetBandwidth) {
  std::vector<mila::Point> points = {{0.0f, 1.0f, 0.0f, 0.0f},
                                   {2.0f, 3.0f, 0.0f, 0.0f},
                                   {10.0f, 11.0f, 0.0f, 0.0f},
                                   {12.0f, 13.0f, 0.0f, 0.0f}
  };
  float bandwidth = 3.0f;
  mila::ParallelMeanShiftProfiler mean_shift;
  mean_shift.Run(points, bandwidth);
  EXPECT_GT(mean_shift.GetBandwidth(), 0);
}
