#include "gtest/gtest.h"
#include "mean_shift_parallel_profiler.h"

class ParallelMeanShiftProfilerTest : public testing::Test {
 protected:
  virtual void SetUp() {
    auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, nullptr);
    auto profiler = std::unique_ptr<mila::Profiler>(new mila::ProfilerStub());
    auto mean_shift = std::unique_ptr<mila::ParallelMeanShift>(new mila::ParallelMeanShift(std::move(ocl_app),
                                                                                           nullptr));
    auto mean_shift_profiler = new mila::ParallelMeanShiftProfiler(std::move(mean_shift), std::move(profiler), nullptr);
    mean_shift_ = std::unique_ptr<mila::ParallelMeanShiftProfiler>(mean_shift_profiler);
  }
  std::unique_ptr<mila::ParallelMeanShiftProfiler> mean_shift_;
};

TEST_F(ParallelMeanShiftProfilerTest, GetResultsAfterInitialize) {
  this->mean_shift_->Initialize();
  EXPECT_GT(this->mean_shift_->GetResults().initialize_duration.count(), 0);
}

TEST_F(ParallelMeanShiftProfilerTest, GetResultsAfterRun) {
  const auto points = std::vector<mila::Point>{{0.0f, 1.0f, 0.0f, 0.0f},
                                               {2.0f, 3.0f, 0.0f, 0.0f},
                                               {10.0f, 11.0f, 0.0f, 0.0f},
                                               {12.0f, 13.0f, 0.0f, 0.0f}
  };
  const auto bandwidth = 3.0f;

  this->mean_shift_->Initialize();
  this->mean_shift_->Run(points, bandwidth);
  EXPECT_GT(this->mean_shift_->GetResults().read_buffer_with_output_duration.count(), 0);
  EXPECT_GT(this->mean_shift_->GetResults().mean_shift_duration.count(), 0);
  EXPECT_GT(this->mean_shift_->GetResults().points_per_second, 0.0f);
  EXPECT_GT(this->mean_shift_->GetResults().bandwidth, 0.0f);

  EXPECT_GT(this->mean_shift_->GetResults().enqueue_nd_range_durations.size(), 0);
  for (const auto &d : this->mean_shift_->GetResults().enqueue_nd_range_durations) {
    EXPECT_GT(d.count(), 0);
  }

  EXPECT_GT(this->mean_shift_->GetResults().read_buffer_with_distances_durations.size(), 0);
  for (const auto &d : this->mean_shift_->GetResults().read_buffer_with_distances_durations) {
    EXPECT_GT(d.count(), 0);
  }

  EXPECT_GT(this->mean_shift_->GetResults().copy_buffer_durations.size(), 0);
  for (const auto &d : this->mean_shift_->GetResults().copy_buffer_durations) {
    EXPECT_GT(d.count(), 0);
  }
}
