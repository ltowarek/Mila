#ifndef MILA_MEAN_SHIFT_PARALLEL_H_
#define MILA_MEAN_SHIFT_PARALLEL_H_

#include <cstddef>

#include "clpp.h"

namespace mila {
namespace meanshift {
namespace parallel {

std::vector<cl_float4> ConvertVectorToPoints(const std::vector<uint8_t> &data);
std::vector<uint8_t> ConvertPointsToVector(const std::vector<cl_float4> &data);

class MeanShift {
 public:
  MeanShift();
  MeanShift(size_t platform_id, size_t device_id);
  MeanShift(size_t platform_id, size_t device_id, float precision, size_t max_iterations);

  float precision() const;
  size_t max_iterations() const;
  size_t platform_id() const;
  size_t device_id() const;

 private:
  const float precision_;
  const size_t max_iterations_;
  const size_t platform_id_;
  const size_t device_id_;
};

}  // parallel
}  // meanshift
}  // mila

#endif  // MILA_MEAN_SHIFT_PARALLEL_H_
