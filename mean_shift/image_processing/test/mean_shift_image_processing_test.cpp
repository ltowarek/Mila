#include "gtest/gtest.h"
#include "mean_shift_image_processing_app.h"

TEST(MeanShiftImageProcessingProfilerTest, GetResultsAfterRun) {
  auto profiler = std::unique_ptr<mila::Profiler>(new mila::ProfilerStub());
  auto mean_shift = std::unique_ptr<mila::MeanShiftImageProcessing>(new mila::MeanShiftImageProcessingStub());
  auto mean_shift_profiler =
      std::unique_ptr<mila::MeanShiftImageProcessingProfiler>(new mila::MeanShiftImageProcessingProfiler(
          std::move(mean_shift),
          std::move(profiler),
          nullptr));

  const auto input_file = std::string("test_image.png");
  const auto output_file = std::string("test_image_output.png");
  const auto bandwidth = 25.0f;

  mean_shift_profiler->Run(input_file, output_file, bandwidth);
  EXPECT_GT(mean_shift_profiler->GetResults().pixels_per_second, 0.0f);
  EXPECT_GT(mean_shift_profiler->GetResults().mean_shift_image_processing_duration.count(), 0);
}

TEST(SequentialMeanShiftImageProcessingAppTest, Run) {
  const auto logger_spy = std::shared_ptr<mila::LoggerSpy>(new mila::LoggerSpy());
  const auto input_file = std::string("test_image.png");
  const auto output_file = std::string("test_image_output.png");
  const auto bandwidth = std::string("25.000000");
  const auto number_of_iterations = std::string("2");
  const char *parameters[] = {"app", input_file.c_str(), output_file.c_str(),
                              bandwidth.c_str(), number_of_iterations.c_str()};
  const auto mean_shift = mila::SequentialMeanShiftImageProcessingApp(logger_spy);
  // const_cast due to C vs C++ string literals
  mean_shift.Run(5, const_cast<char **>(parameters));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Input file: " + input_file));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Output file: " + output_file));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Bandwidth: " + bandwidth));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of iterations: " + number_of_iterations));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift image processing duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift image processing duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift image processing duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift image processing duration coefficient of variation: "));
}

TEST(ParallelMeanShiftImageProcessingAppTest, Run) {
  const auto logger_spy = std::shared_ptr<mila::LoggerSpy>(new mila::LoggerSpy());
  const auto input_file = std::string("test_image.png");
  const auto output_file = std::string("test_image_output.png");
  const auto bandwidth = std::string("25.000000");
  const auto platform_id = std::string("0");
  const auto device_id = std::string("0");
  const auto number_of_iterations = std::string("2");
  const char *parameters[] = {"app", input_file.c_str(), output_file.c_str(),
                              bandwidth.c_str(), platform_id.c_str(), device_id.c_str(), number_of_iterations.c_str()};
  const auto mean_shift = mila::ParallelMeanShiftImageProcessingApp(logger_spy);
  // const_cast due to C vs C++ string literals
  mean_shift.Run(7, const_cast<char **>(parameters));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Input file: " + input_file));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Output file: " + output_file));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Bandwidth: " + bandwidth));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Platform id: " + platform_id));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Device id: " + device_id));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of iterations: " + number_of_iterations));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift image processing duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift image processing duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift image processing duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mean shift image processing duration coefficient of variation: "));
}
