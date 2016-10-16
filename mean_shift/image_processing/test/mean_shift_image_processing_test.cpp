#include "gtest/gtest.h"
#include "mean_shift_image_processing_profiler.h"

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
