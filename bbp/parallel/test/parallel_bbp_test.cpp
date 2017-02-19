#include <chrono>
#include <list>
#include <thread>
#include "gtest/gtest.h"
#include "bbp_parallel.hpp"
#include "bbp_parallel_profiler.hpp"
#include "bbp_parallel_app.hpp"

class ParallelBBPProfilerTest : public testing::Test {
 protected:
  virtual void SetUp() {
    auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, nullptr);
    auto profiler = std::unique_ptr<mila::Profiler>(new mila::ProfilerStub());
    auto bbp = std::unique_ptr<mila::ParallelBBP>(new mila::ParallelBBP(std::move(ocl_app),
                                                                        nullptr));
    auto bbp_profiler = new mila::ParallelBBPProfiler(std::move(bbp), std::move(profiler), nullptr);
    bbp_ = std::unique_ptr<mila::ParallelBBPProfiler>(bbp_profiler);
  }
  std::unique_ptr<mila::ParallelBBPProfiler> bbp_;
};

TEST_F(ParallelBBPProfilerTest, GetResultsAfterInitialize) {
  this->bbp_->Initialize();
  EXPECT_GT(this->bbp_->GetResults().initialize_duration.count(), 0);
}

TEST_F(ParallelBBPProfilerTest, GetResultsAfterComputeDigits) {
  this->bbp_->Initialize();
  this->bbp_->ComputeDigits(24, 516);
  EXPECT_GT(this->bbp_->GetResults().compute_digits_duration.count(), 0);
  EXPECT_GT(this->bbp_->GetResults().read_buffer_duration.count(), 0);
  EXPECT_GT(this->bbp_->GetResults().enqueue_nd_range_duration.count(), 0);
  EXPECT_GT(this->bbp_->GetResults().digits_per_second, 0.0f);
  EXPECT_GT(this->bbp_->GetResults().bandwidth, 0.0f);
}

TEST(ParallelBBPAppTest, Run) {
  auto logger_spy = std::shared_ptr<mila::LoggerSpy>(new mila::LoggerSpy());
  auto number_of_digits = std::string("5");
  auto starting_position = std::string("100");
  auto platform_id = std::string("0");
  auto device_id = std::string("0");
  auto number_of_iterations = std::string("10");
  auto expected_output = std::string("29B7C");
  const char *parameters[] =
      {"app", number_of_digits.c_str(), starting_position.c_str(), platform_id.c_str(), device_id.c_str(),
       number_of_iterations.c_str()};
  auto bbp = mila::ParallelBBPApp(logger_spy);
  // const_cast due to C vs C++ string literals
  bbp.Run(6, const_cast<char **>(parameters));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of digits: " + number_of_digits));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Starting position: " + starting_position));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Platform id: " + platform_id));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Device id: " + device_id));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of iterations: " + number_of_iterations));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Platform name: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Device name: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Digits: " + expected_output));
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
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Compute digits duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Compute digits duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Compute digits duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Compute digits duration coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Enqueue ND range duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Enqueue ND range duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Enqueue ND range duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Enqueue ND range duration coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Read buffer duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Read buffer duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Read buffer duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Read buffer duration coefficient of variation: "));
}