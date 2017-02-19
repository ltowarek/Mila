#ifndef MILA_MEAN_SHIFT_IMAGE_PROCESSING_PROFILER_H
#define MILA_MEAN_SHIFT_IMAGE_PROCESSING_PROFILER_H

#include "mean_shift_image_processing.hpp"
#include "profiler.hpp"
#include "utils.hpp"

namespace mila {
struct MeanShiftImageProcessingProfilingResults {
  std::chrono::microseconds mean_shift_image_processing_duration;
  float pixels_per_second;
};

class MeanShiftImageProcessingProfiler : public MeanShiftImageProcessing {
 public:
  MeanShiftImageProcessingProfiler(std::unique_ptr<mila::MeanShiftImageProcessing> mean_shift,
                                   std::unique_ptr<Profiler> profiler,
                                   const std::shared_ptr<mila::Logger> logger);

  void Run(const std::string &input_file, const std::string &output_file, const float bandwidth) override;

  MeanShiftImageProcessingProfilingResults GetResults() const;
 private:
  const std::unique_ptr<mila::MeanShiftImageProcessing> mean_shift_;
  const std::unique_ptr<mila::Profiler> profiler_;
  const std::shared_ptr<mila::Logger> logger_;
  MeanShiftImageProcessingProfilingResults results_;

  void InitResults();
  void SetResultsAfterRun(const size_t number_of_pixels);
};
}  // mila
#endif  // MILA_MEAN_SHIFT_IMAGE_PROCESSING_PROFILER_H
