#ifndef MILA_MEAN_SHIFT_SEQUENTIAL_H_
#define MILA_MEAN_SHIFT_SEQUENTIAL_H_

#include <cmath>
#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

#include "logger.h"
#include "mean_shift.h"
#include "mean_shift_utils.h"

namespace mila {

std::vector<Point> ConvertVectorToPoints(const std::vector<uint8_t> &data);
std::vector<uint8_t> ConvertPointsToVector(const std::vector<Point> &data);

class SequentialMeanShift : public MeanShift {
 public:
  SequentialMeanShift(const std::shared_ptr<mila::Logger> logger);
  virtual ~SequentialMeanShift() override;

  virtual std::vector<Point> Run(const std::vector<Point> &points, const float bandwidth) override;

  Point ShiftPoint(const Point &point, const std::vector<Point> &points, const float bandwidth) const;
  float Distance(const Point &point1, const Point &point2) const;
  float GaussianKernel(const float x, const float sigma) const;
 private:
  const std::shared_ptr<mila::Logger> logger_;
};

class MeanShiftImageProcessing {
 public:
  MeanShiftImageProcessing(std::unique_ptr<mila::MeanShift> mean_shift,
                           const std::shared_ptr<mila::Logger> logger);
  virtual void Run(const std::string &input_file, const std::string &output_file, float bandwidth);
 private:
  const std::shared_ptr<mila::Logger> logger_;
  const std::unique_ptr<mila::MeanShift> mean_shift_;
};
}  // mila
#endif  // MILA_MEAN_SHIFT_SEQUENTIAL_H_
