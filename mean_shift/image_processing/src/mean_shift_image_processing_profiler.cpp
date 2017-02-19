#include "mean_shift_image_processing_profiler.hpp"

mila::MeanShiftImageProcessingProfiler::MeanShiftImageProcessingProfiler(std::unique_ptr<mila::MeanShiftImageProcessing> mean_shift,
                                                                         std::unique_ptr<mila::Profiler> profiler,
                                                                         const std::shared_ptr<mila::Logger> logger)
    : mean_shift_(std::move(mean_shift)),
      profiler_(std::move(profiler)),
      logger_(logger) {
  InitResults();
}

void mila::MeanShiftImageProcessingProfiler::Run(const std::string &input_file,
                                                 const std::string &output_file,
                                                 const float bandwidth) {
  profiler_->Start("Run");
  mean_shift_->Run(input_file, output_file, bandwidth);
  profiler_->End("Run");
  const auto number_of_pixels = ConvertVectorToPoints(mila::Image(input_file).Read()).size();
  SetResultsAfterRun(number_of_pixels);
}

mila::MeanShiftImageProcessingProfilingResults mila::MeanShiftImageProcessingProfiler::GetResults() const {
  return results_;
}

void mila::MeanShiftImageProcessingProfiler::InitResults() {
  results_.mean_shift_image_processing_duration = std::chrono::seconds(0);
  results_.pixels_per_second = 0.0f;
}

void mila::MeanShiftImageProcessingProfiler::SetResultsAfterRun(const size_t number_of_pixels) {
  results_.mean_shift_image_processing_duration = profiler_->GetDuration("Run");
  results_.pixels_per_second = mila::GetValuePerSecond(number_of_pixels,
                                                              results_.mean_shift_image_processing_duration);
}
