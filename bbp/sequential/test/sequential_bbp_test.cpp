#include "gtest/gtest.h"
#include "bbp_sequential.hpp"
#include "bbp_sequential_profiler.hpp"
#include "bbp_sequential_app.hpp"

TEST(BBPSequentialTest, FloatPrecision) {
  EXPECT_NEAR(powf(8 * 100 + 6, 2), 649636, 1e-5);
  EXPECT_NEAR(powf(8 * 1000 + 6, 2), 64096036, 1e-5);
  EXPECT_NEAR(pow(8 * 10000 + 6, 2), 6400960036, 1e-5);
  EXPECT_NEAR(pow(8 * 100000 + 6, 2), 640009600036, 1e-5);
  EXPECT_NEAR(pow(8 * 1000000 + 6, 2), 64000096000036, 1e-5);
  EXPECT_NEAR(pow(8 * 10000000 + 6, 2), 6400000960000036, 1e-5);
  EXPECT_NEAR(pow(8 * 100000000 + 6, 2), 640000009600000036, 1e-5);
}

TEST(BBPSequentialTest, ComputeDigit) {
  mila::SequentialBBP bbp(nullptr);
  EXPECT_NEAR(bbp.ComputeDigit(0), 0.141587316989899f, 1e-5f);
  EXPECT_NEAR(bbp.ComputeDigit(1), 0.265479207038879f, 1e-5f);
  EXPECT_NEAR(bbp.ComputeDigit(500), 1.5261161327362061f, 1e-5f);
}

TEST(BBPSequentialTest, Series) {
  mila::SequentialBBP bbp(nullptr);
  EXPECT_NEAR(bbp.Series(1, 500), 0.86922550201416016f, 1e-5f);
  EXPECT_NEAR(bbp.Series(4, 500), 0.29369428753852844f, 1e-5f);
  EXPECT_NEAR(bbp.Series(5, 500), 0.76753216981887817f, 1e-5f);
  EXPECT_NEAR(bbp.Series(6, 500), 0.59586530923843384f, 1e-5f);
}

TEST(BBPSequentialTest, LargestPowerOfTwoLessOrEqual) {
  mila::SequentialBBP bbp(nullptr);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(0), 0);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(1), 1);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(2), 2);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(3), 2);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(4), 3);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(5), 3);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(10), 4);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(100), 7);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(1000), 10);
  EXPECT_EQ(bbp.LargestPowerOfTwoLessOrEqual(33554432), 26);
}

TEST(BBPSequentialTest, ModularExponentiation) {
  mila::SequentialBBP bbp(nullptr);
  EXPECT_EQ(bbp.ModularExponentiation(0.0f, 0.0f, 0), 1.0f);
  EXPECT_EQ(bbp.ModularExponentiation(0.0f, 1.0f, 0), 0.0f);
  EXPECT_EQ(bbp.ModularExponentiation(16.0f, 1.0f, 0), 0.0f);
  EXPECT_EQ(bbp.ModularExponentiation(16.0f, 1.0f, 1), 0.0f);
  EXPECT_EQ(bbp.ModularExponentiation(16.0f, 1.0f, 5), 0.0f);
  EXPECT_EQ(bbp.ModularExponentiation(16.0f, 16.0f, 16), 0.0f);
  EXPECT_EQ(bbp.ModularExponentiation(16.0f, 7.0f, 2), 4.0f);
  EXPECT_EQ(bbp.ModularExponentiation(5.0f, 13.0f, 3), 8.0f);
  EXPECT_EQ(bbp.ModularExponentiation(8.5f, 3.25f, 2), 0.75f);
  EXPECT_EQ(bbp.ModularExponentiation(16.0f, 121.0f, 999985), 56.0f);
}

class SequentialBBPProfilerTest : public testing::Test {
 protected:
  virtual void SetUp() {
    auto bbp = std::unique_ptr<mila::SequentialBBP>(new mila::SequentialBBP(nullptr));
    auto profiler = std::unique_ptr<mila::Profiler>(new mila::ProfilerStub());
    auto bbp_profiler = new mila::SequentialBBPProfiler(std::move(bbp), std::move(profiler), nullptr);
    bbp_ = std::unique_ptr<mila::SequentialBBPProfiler>(bbp_profiler);
  }
  std::unique_ptr<mila::SequentialBBPProfiler> bbp_;
};

TEST_F(SequentialBBPProfilerTest, GetResultsAfterComputeDigits) {
  this->bbp_->ComputeDigits(24, 516);
  EXPECT_GT(this->bbp_->GetResults().compute_digits_duration.count(), 0);
  EXPECT_GT(this->bbp_->GetResults().digits_per_second, 0.0f);
}

TEST(SequentialBBPAppTest, Run) {
  auto logger_spy = std::shared_ptr<mila::LoggerSpy>(new mila::LoggerSpy());
  auto number_of_digits = std::string("5");
  auto starting_position = std::string("100");
  auto number_of_iterations = std::string("10");
  auto expected_output = std::string("29B7C");
  const char *parameters[] = {"app", number_of_digits.c_str(), starting_position.c_str(), number_of_iterations.c_str()};
  auto bbp = mila::SequentialBBPApp(logger_spy);
  // const_cast due to C vs C++ string literals
  bbp.Run(6, const_cast<char **>(parameters));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of digits: " + number_of_digits));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Starting position: " + starting_position));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of iterations: " + number_of_iterations));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Digits: " + expected_output));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Compute digits duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Compute digits duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Compute digits duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Compute digits duration coefficient of variation: "));
}
