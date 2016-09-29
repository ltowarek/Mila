#include "gtest/gtest.h"
#include "mean_shift_sequential.h"
#include "mean_shift_sequential_profiler.h"
#include "mean_shift_sequential_app.h"

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

class SequentialMeanShiftProfilerTest : public testing::Test {
 protected:
  virtual void SetUp() {
    auto mean_shift = std::unique_ptr<mila::SequentialMeanShift>(new mila::SequentialMeanShift(nullptr));
    auto profiler = std::unique_ptr<mila::Profiler>(new mila::ProfilerStub());
    auto mean_shift_profiler =
        new mila::SequentialMeanShiftProfiler(std::move(mean_shift), std::move(profiler), nullptr);
    mean_shift_ = std::unique_ptr<mila::SequentialMeanShiftProfiler>(mean_shift_profiler);
  }
  std::unique_ptr<mila::SequentialMeanShiftProfiler> mean_shift_;
};

TEST_F(SequentialMeanShiftProfilerTest, GetResultsAfterRun) {
  const auto points = std::vector<mila::Point>{{0.0f, 1.0f, 0.0f, 0.0f},
                                               {2.0f, 3.0f, 0.0f, 0.0f},
                                               {10.0f, 11.0f, 0.0f, 0.0f},
                                               {12.0f, 13.0f, 0.0f, 0.0f}
  };
  const auto bandwidth = 3.0f;

  this->mean_shift_->Run(points, bandwidth);

  EXPECT_GT(this->mean_shift_->GetResults().mean_shift_duration.count(), 0);
  EXPECT_GT(this->mean_shift_->GetResults().points_per_second, 0.0f);
}

TEST(SequentialMeanShiftAppTest, Run) {
  const auto logger_spy = std::shared_ptr<mila::LoggerSpy>(new mila::LoggerSpy());
  const auto number_of_points = std::string("2");
  const auto points = std::string("0.000000 1.000000 0.000000 0.000000\n"
                                      "2.000000 3.000000 0.000000 0.000000\n");
  const auto bandwidth = std::string("3.000000");
  const auto number_of_iterations = std::string("10");
  const auto expected_output = std::string("0.999999 1.999999 0.000000 0.000000\n"
                                               "1.000001 2.000001 0.000000 0.000000\n");
  const char *parameters[] = {"app", number_of_points.c_str(),
                              "0.0f", "1.0f", "0.0f", "0.0f",
                              "2.0f", "3.0f", "0.0f", "0.0f",
                              bandwidth.c_str(), number_of_iterations.c_str()};
  const auto mean_shift = mila::SequentialMeanShiftApp(logger_spy);
  // const_cast due to C vs C++ string literals
  mean_shift.Run(12, const_cast<char **>(parameters));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Points:\n" + points));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Bandwidth: " + bandwidth));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of iterations: " + number_of_iterations));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Output:\n" + expected_output));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift duration coefficient of variation: "));
}
