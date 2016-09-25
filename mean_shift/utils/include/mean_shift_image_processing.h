#ifndef MILA_UTILS_MEAN_SHIFT_IMAGE_PROCESSING_H_
#define MILA_UTILS_MEAN_SHIFT_IMAGE_PROCESSING_H_

#include <chrono>
#include <vector>
#include <map>
#include <memory>
#include <string>

#include "mean_shift.h"
#include "mean_shift_utils.h"
#include "logger.h"
#include "utils.h"

namespace mila {
class MeanShiftImageProcessing {
 public:
  MeanShiftImageProcessing(std::unique_ptr<mila::MeanShift> mean_shift,
                           const std::shared_ptr<mila::Logger> logger);
  virtual void Run(const std::string &input_file, const std::string &output_file, const float bandwidth);
 private:
  const std::shared_ptr<mila::Logger> logger_;
  const std::unique_ptr<mila::MeanShift> mean_shift_;
};

class MeanShiftImageProcessingProfiler : public MeanShiftImageProcessing {
 public:
  MeanShiftImageProcessingProfiler(std::unique_ptr<mila::MeanShift> mean_shift,
                                   const std::shared_ptr<mila::Logger> logger);

  void Run(const std::string &input_file, const std::string &output_file, const float bandwidth) override;

  std::string main_result() const;
  std::string main_duration() const;
  std::map<std::string, float> results() const;
 private:
  const std::string main_result_;
  const std::string main_duration_;
  std::map<std::string, float> results_;
  size_t number_of_points_;
};
}  // mila
#endif  // MILA_UTILS_MEAN_SHIFT_IMAGE_PROCESSING_H_
