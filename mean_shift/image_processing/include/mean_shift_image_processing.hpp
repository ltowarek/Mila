#ifndef MILA_MEAN_SHIFT_IMAGE_PROCESSING_H
#define MILA_MEAN_SHIFT_IMAGE_PROCESSING_H

#include "mean_shift.hpp"
#include "logger.hpp"
#include "mean_shift_utils.hpp"

namespace mila {
class MeanShiftImageProcessing {
 public:
  virtual ~MeanShiftImageProcessing() = default;
  virtual void Run(const std::string &input_file, const std::string &output_file, const float bandwidth) = 0;
};

class GenericMeanShiftImageProcessing : public MeanShiftImageProcessing {
 public:
  GenericMeanShiftImageProcessing(std::unique_ptr<mila::MeanShift> mean_shift,
                                  const std::shared_ptr<mila::Logger> logger);
  void Run(const std::string &input_file, const std::string &output_file, const float bandwidth) override;
 private:
  const std::shared_ptr<mila::Logger> logger_;
  const std::unique_ptr<mila::MeanShift> mean_shift_;
};

class MeanShiftImageProcessingStub : public MeanShiftImageProcessing {
 public:
  virtual void Run(const std::string &input_file, const std::string &output_file, const float bandwidth) override {

  }
};
}  // mila
#endif  // MILA_MEAN_SHIFT_IMAGE_PROCESSING_H
