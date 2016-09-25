#include "gtest/gtest.h"
#include "mean_shift_sequential.h"
#include "mean_shift_sequential_profiler.h"
#include "mean_shift_image_processing.h"

TEST(SequentialMeanShiftSequentialTest, DistanceZero) {
  mila::SequentialMeanShift mean_shift(nullptr);
  mila::Point point1 = {0.0f};
  mila::Point point2 = {0.0f};
  EXPECT_EQ(mean_shift.Distance(point1, point2), 0.0f);
}

TEST(SequentialMeanShiftSequentialTest, DistanceComplex) {
  mila::SequentialMeanShift mean_shift(nullptr);
  mila::Point point1 = {-7.0f, -4.0f, 3.0f, 0.0f};
  mila::Point point2 = {17.0f, 6.0f, 2.5f, 0.0f};
  EXPECT_NEAR(mean_shift.Distance(point1, point2), 26.00480f, 1e-5f);
}

TEST(SequentialMeanShiftSequentialTest, GaussianKernelZero) {
  mila::SequentialMeanShift mean_shift(nullptr);
  float x = 0.0f;
  float sigma = 1.0f;
  EXPECT_NEAR(mean_shift.GaussianKernel(x, sigma), 0.39894f, 1e-5f);
}

TEST(SequentialMeanShiftSequentialTest, GaussianKernelUndefined) {
  mila::SequentialMeanShift mean_shift(nullptr);
  float x = 0.0f;
  float sigma = 0.0f;
  EXPECT_NEAR(mean_shift.GaussianKernel(x, sigma), 0.0f, 1e-5f);
}

TEST(SequentialMeanShiftSequentialTest, GaussianKernelComplex) {
  mila::SequentialMeanShift mean_shift(nullptr);
  float x = 2.25f;
  float sigma = 2.0f;
  EXPECT_NEAR(mean_shift.GaussianKernel(x, sigma), 0.10593f, 1e-5f);
}

TEST(SequentialMeanShiftSequentialTest, ShiftPointZero) {
  mila::SequentialMeanShift mean_shift(nullptr);
  mila::Point point = {0.0f};
  std::vector<mila::Point> points = {{1.0f}, {-1.0f}};
  float bandwidth = 1.0f;

  mila::Point output = mean_shift.ShiftPoint(point, points, bandwidth);

  EXPECT_NEAR(output.x, 0.0f, 1e-5f);
  EXPECT_NEAR(output.y, 0.0f, 1e-5f);
  EXPECT_NEAR(output.z, 0.0f, 1e-5f);
  EXPECT_NEAR(output.w, 0.0f, 1e-5f);
}

TEST(SequentialMeanShiftSequentialTest, ShiftPointUndefined) {
  mila::SequentialMeanShift mean_shift(nullptr);
  mila::Point point = {0.0f};
  std::vector<mila::Point> points = {{1.0f}, {-1.0f}};
  float bandwidth = 0.0f;

  mila::Point output = mean_shift.ShiftPoint(point, points, bandwidth);

  EXPECT_NEAR(output.x, 0.0f, 1e-5f);
  EXPECT_NEAR(output.y, 0.0f, 1e-5f);
  EXPECT_NEAR(output.z, 0.0f, 1e-5f);
  EXPECT_NEAR(output.w, 0.0f, 1e-5f);
}

TEST(SequentialMeanShiftSequentialTest, ShiftPointSimple) {
  mila::SequentialMeanShift mean_shift(nullptr);
  mila::Point point = {0.0f};
  std::vector<mila::Point> points = {{1.0f, 1.0f, 0.0f, 0.0f}, {-2.0f, -2.0f, 0.0f, 0.0f}};
  float bandwidth = 2.0f;

  mila::Point output = mean_shift.ShiftPoint(point, points, bandwidth);

  EXPECT_NEAR(output.x, 0.037536f, 1e-5f);
  EXPECT_NEAR(output.y, 0.037536f, 1e-5f);
  EXPECT_NEAR(output.z, 0.0f, 1e-5f);
  EXPECT_NEAR(output.w, 0.0f, 1e-5f);
}

TEST(SequentialMeanShiftSequentialTest, ShiftPointComplex) {
  mila::SequentialMeanShift mean_shift(nullptr);
  mila::Point point = {1.0f, -5.0f, 8.0f, 0.0f};
  std::vector<mila::Point>
      points = {{1.5f, 1.0f, -10.0f, 0.0f}, {-2.0f, 20.0f, -1.25f, 0.0f}, {5.5f, 7.3f, -8.75f, 0.0f}};
  float bandwidth = 2.0f;

  mila::Point output = mean_shift.ShiftPoint(point, points, bandwidth);

  EXPECT_NEAR(output.x, 1.50004f, 1e-5f);
  EXPECT_NEAR(output.y, 1.00006f, 1e-5f);
  EXPECT_NEAR(output.z, -9.99998f, 1e-5f);
  EXPECT_NEAR(output.w, 0.0f, 1e-5f);
}

TEST(SequentialMeanShiftProfilerTest, RunWithProfiling) {
  mila::SequentialMeanShiftProfiler mean_shift;

  std::vector<mila::Point> points = {{0.0f, 1.0f, 0.0f, 0.0f},
                                     {2.0f, 3.0f, 0.0f, 0.0f},
                                     {10.0f, 11.0f, 0.0f, 0.0f},
                                     {12.0f, 13.0f, 0.0f, 0.0f}
  };
  float bandwidth = 3.0f;

  EXPECT_EQ(mean_shift.results().count("Points per second"), 0);
  EXPECT_EQ(mean_shift.results().count("Run"), 0);
  mean_shift.Run(points, bandwidth);
  EXPECT_EQ(mean_shift.results().count("Points per second"), 1);
  EXPECT_EQ(mean_shift.results().count("Run"), 1);
}

TEST(MeanShiftImageProcessingTest, RunWithImage) {
  auto m = std::unique_ptr<mila::MeanShift>(new mila::SequentialMeanShift(std::shared_ptr<mila::Logger>()));
  mila::MeanShiftImageProcessing mean_shift(std::move(m), nullptr);
  std::string input_file = "test_image.png";
  std::string output_file = "test_image_output.png";
  std::string reference_file = "test_image_reference.png";
  float bandwidth = 25.0f;

  mean_shift.Run(input_file, output_file, bandwidth);

  mila::Image output_image(output_file);
  std::vector<uint8_t> output = output_image.Read();

  mila::Image reference_image(reference_file);
  std::vector<uint8_t> reference = reference_image.Read();

  for (size_t i = 0; i < reference.size(); ++i) {
    EXPECT_EQ(output[i], reference[i]);
  }
}

TEST(MeanShiftImageProcessingProfilerTest, RunWithImage) {
  auto m = std::unique_ptr<mila::MeanShift>(new mila::SequentialMeanShift(std::shared_ptr<mila::Logger>()));
  mila::MeanShiftImageProcessingProfiler mean_shift(std::move(m), nullptr);
  std::string input_file = "test_image.png";
  std::string output_file = "test_image_output.png";
  std::string reference_file = "test_image_reference.png";
  float bandwidth = 25.0f;

  mean_shift.Run(input_file, output_file, bandwidth);

  mila::Image output_image(output_file);
  std::vector<uint8_t> output = output_image.Read();

  mila::Image reference_image(reference_file);
  std::vector<uint8_t> reference = reference_image.Read();

  for (size_t i = 0; i < reference.size(); ++i) {
    EXPECT_EQ(output[i], reference[i]);
  }
}

TEST(MeanShiftImageProcessingProfilerTest, RunWithImageWithProfiling) {
  auto m = std::unique_ptr<mila::MeanShift>(new mila::SequentialMeanShift(std::shared_ptr<mila::Logger>()));
  mila::MeanShiftImageProcessingProfiler mean_shift(std::move(m), nullptr);
  std::string input_file = "test_image.png";
  std::string output_file = "test_image_output.png";
  float bandwidth = 25.0f;

  EXPECT_EQ(mean_shift.results().count("RunWithImage"), 0);
  EXPECT_EQ(mean_shift.results().count("Pixels per second"), 0);
  mean_shift.Run(input_file, output_file, bandwidth);
  EXPECT_EQ(mean_shift.results().count("RunWithImage"), 1);
  EXPECT_EQ(mean_shift.results().count("Pixels per second"), 1);
}
