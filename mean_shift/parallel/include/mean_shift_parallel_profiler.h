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
  std::string main_duration() const;
  std::map<std::string, float> results() const;
 private:
  const std::string main_result_;
  const std::string main_duration_;
  std::map<std::string, float> results_;
};

class MeanShiftImageProcessingProfiler: public MeanShiftImageProcessing {
 public:
  MeanShiftImageProcessingProfiler();
  MeanShiftImageProcessingProfiler(size_t platform_id, size_t device_id);
  MeanShiftImageProcessingProfiler(size_t platform_id, size_t device_id, float precision, size_t max_iterations);

  void Initialize() override;
  virtual std::vector<cl_float4> Run(const std::vector<cl_float4> &points, float bandwidth) override;
  virtual void Run(const std::string &input_file, const std::string &output_file, float bandwidth);

  std::string main_result() const;
  std::string main_duration() const;
  std::map<std::string, float> results() const;
 private:
  const std::string main_result_;
  const std::string main_duration_;
  size_t number_of_points_;
  std::map<std::string, float> results_;
};

}  // parallel
}  // meanshift
}  // mila

#endif  // MILA_MEAN_SHIFT_PARALLEL_PROFILER_H_
