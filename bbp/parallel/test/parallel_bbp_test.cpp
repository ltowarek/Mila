#include <chrono>
#include <list>
#include <thread>
#include "gtest/gtest.h"
#include "bbp_parallel.h"
#include "bbp_parallel_profiler.h"
#include "bbp_parallel_app.h"

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

std::vector<std::string> logger_spy_messages;

class LoggerSpy : public mila::Logger {
 public:
  LoggerSpy() {
    logger_spy_messages.clear();
  }
  virtual ~LoggerSpy() override {

  }
  virtual void SetLevel(mila::LEVELS level) override {

  }
  virtual void Critical(const char *message, ...) const override {
    va_list args1;
    va_start(args1, message);
    va_list args2;
    va_copy(args2, args1);
    auto output = std::vector<char>(1ul + vsnprintf(nullptr, 0, message, args1));
    va_end(args1);
    vsnprintf(output.data(), output.size(), message, args2);
    va_end(args2);
    logger_spy_messages.push_back("C " + std::string(output.data()));
  }
  virtual void Error(const char *message, ...) const override {
    va_list args1;
    va_start(args1, message);
    va_list args2;
    va_copy(args2, args1);
    auto output = std::vector<char>(1ul + vsnprintf(nullptr, 0, message, args1));
    va_end(args1);
    vsnprintf(output.data(), output.size(), message, args2);
    va_end(args2);
    logger_spy_messages.push_back("E " + std::string(output.data()));
  }
  virtual void Warning(const char *message, ...) const override {
    va_list args1;
    va_start(args1, message);
    va_list args2;
    va_copy(args2, args1);
    auto output = std::vector<char>(1ul + vsnprintf(nullptr, 0, message, args1));
    va_end(args1);
    vsnprintf(output.data(), output.size(), message, args2);
    va_end(args2);
    logger_spy_messages.push_back("W " + std::string(output.data()));
  }
  virtual void Info(const char *message, ...) const override {
    va_list args1;
    va_start(args1, message);
    va_list args2;
    va_copy(args2, args1);
    auto output = std::vector<char>(1ul + vsnprintf(nullptr, 0, message, args1));
    va_end(args1);
    vsnprintf(output.data(), output.size(), message, args2);
    va_end(args2);
    logger_spy_messages.push_back("I " + std::string(output.data()));
  }
  virtual void Debug(const char *message, ...) const override {
    va_list args1;
    va_start(args1, message);
    va_list args2;
    va_copy(args2, args1);
    auto output = std::vector<char>(1ul + vsnprintf(nullptr, 0, message, args1));
    va_end(args1);
    vsnprintf(output.data(), output.size(), message, args2);
    va_end(args2);
    logger_spy_messages.push_back("D " + std::string(output.data()));
  }
};

bool contains_str(const std::vector<std::string> &v, const std::string str) {
  return
      std::find_if(v.begin(), v.end(),
                   [str](const std::string &s) -> bool { return s.find(str) != std::string::npos; }) != v.end();
}

TEST(ParallelBBPAppTest, Run) {
  auto logger_spy = std::shared_ptr<LoggerSpy>(new LoggerSpy());
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
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Number of digits: " + number_of_digits));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Starting position: " + starting_position));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Platform id: " + platform_id));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Device id: " + device_id));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Number of iterations: " + number_of_iterations));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Platform name: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Device name: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Digits: " + expected_output));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Bandwidth mean: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Bandwidth median: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Bandwidth standard deviation: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Bandwidth coefficient of variation: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Throughput mean: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Throughput median: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Throughput standard deviation: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Throughput coefficient of variation: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Initialize duration mean: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Initialize duration median: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Initialize duration standard deviation: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Initialize duration coefficient of variation: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Compute digits duration mean: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Compute digits duration median: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Compute digits duration standard deviation: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Compute digits duration coefficient of variation: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Enqueue ND range duration mean: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Enqueue ND range duration median: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Enqueue ND range duration standard deviation: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Enqueue ND range duration coefficient of variation: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Read buffer duration mean: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Read buffer duration median: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Read buffer duration standard deviation: "));
  EXPECT_TRUE(contains_str(logger_spy_messages, "I Read buffer duration coefficient of variation: "));
}