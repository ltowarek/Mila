#ifndef MILA_MEAN_SHIFT_PARALLEL_PROFILER_H_
#define MILA_MEAN_SHIFT_PARALLEL_PROFILER_H_

#include <chrono>
#include <map>

#include "mean_shift_parallel.h"

namespace mila {
namespace meanshift {
namespace parallel {

class MeanShiftProfiler: public MeanShift {
 public:
  MeanShiftProfiler();
  MeanShiftProfiler(size_t platform_id, size_t device_id);
  MeanShiftProfiler(size_t platform_id, size_t device_id, float precision, size_t max_iterations);

  void Initialize() override;
  std::vector<cl_float4> Run(const std::vector<cl_float4> &points, float bandwidth) override;

  std::string main_result() const;
  std::map<std::string, int64_t> results() const;
 private:
  const std::string main_result_;
  std::map<std::string, int64_t> results_;
};

}  // parallel
}  // meanshift
}  // mila

#endif  // MILA_MEAN_SHIFT_PARALLEL_PROFILER_H_
