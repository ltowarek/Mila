#ifndef MILA_MEAN_SHIFT_SEQUENTIAL_HPP
#define MILA_MEAN_SHIFT_SEQUENTIAL_HPP

#include <cmath>
#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

#include "logger.hpp"
#include "mean_shift.hpp"
#include "mean_shift_utils.hpp"

namespace mila {
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
}  // mila
#endif  // MILA_MEAN_SHIFT_SEQUENTIAL_HPP
