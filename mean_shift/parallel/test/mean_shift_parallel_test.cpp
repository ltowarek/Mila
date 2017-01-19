#include "gtest/gtest.h"
#include "mean_shift_parallel_profiler.h"
#include "mean_shift_parallel_app.h"

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

TEST(ParallelMeanShiftAppTest, Run) {
  const auto logger_spy = std::shared_ptr<mila::LoggerSpy>(new mila::LoggerSpy());
  const auto number_of_points = std::string("2");
  const auto points = std::string("0.000000 1.000000 0.000000 0.000000\n"
                                      "2.000000 3.000000 0.000000 0.000000\n");
  const auto bandwidth = std::string("3.000000");
  const auto platform_id = std::string("0");
  const auto device_id = std::string("0");
  const auto number_of_iterations = std::string("10");
  const auto expected_output = std::string("0.999999 1.999999 0.000000 0.000000\n"
                                               "1.000001 2.000001 0.000000 0.000000\n");
  const char *parameters[] =
      {"app", number_of_points.c_str(), "0.0f", "1.0f", "0.0f", "0.0f", "2.0f", "3.0f", "0.0f", "0.0f",
       bandwidth.c_str(), platform_id.c_str(), device_id.c_str(),
       number_of_iterations.c_str()};
  const auto mean_shift = mila::ParallelMeanShiftApp(logger_spy);
  // const_cast due to C vs C++ string literals
  mean_shift.Run(14, const_cast<char **>(parameters));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Points:\n" + points));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Bandwidth: " + bandwidth));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Platform id: " + platform_id));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Device id: " + device_id));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of iterations: " + number_of_iterations));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Platform name: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Device name: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Output:\n" + expected_output));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Bandwidth mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Bandwidth median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Bandwidth standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Bandwidth coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Initialize duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Initialize duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Initialize duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Initialize duration coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift duration coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Enqueue ND range durations mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Enqueue ND range durations median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Enqueue ND range durations standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Enqueue ND range durations coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Single enqueue ND range duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Single enqueue ND range duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Single enqueue ND range duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages,
                                "I Single enqueue ND range duration coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Copy buffer durations mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Copy buffer durations median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Copy buffer durations standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Copy buffer durations coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Single copy buffer duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Single copy buffer duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Single copy buffer duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Single copy buffer duration coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Read buffer with output duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Read buffer with output duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Read buffer with output duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages,
                                "I Read buffer with output duration coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Read buffer with distances durations mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Read buffer with distances durations median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages,
                                "I Read buffer with distances durations standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages,
                                "I Read buffer with distances durations coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Single read buffer with distances duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Single read buffer with distances duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages,
                                "I Single read buffer with distances duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages,
                                "I Single read buffer with distances duration coefficient of variation: "));
}
