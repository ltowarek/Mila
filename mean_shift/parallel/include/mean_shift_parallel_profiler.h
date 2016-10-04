#ifndef MILA_MEAN_SHIFT_PARALLEL_PROFILER_H_
#define MILA_MEAN_SHIFT_PARALLEL_PROFILER_H_

#include <chrono>
#include <map>

#include "mean_shift_parallel.h"
#include "statistics.h"
#include "utils.h"

namespace mila {
class ParallelMeanShiftProfiler: public ParallelMeanShift {
 public:
  ParallelMeanShiftProfiler();
  ParallelMeanShiftProfiler(size_t platform_id, size_t device_id);
  ParallelMeanShiftProfiler(size_t platform_id, size_t device_id, float precision, size_t max_iterations);

  void Initialize() override;
  std::vector<Point> Run(const std::vector<Point> &points, float bandwidth) override;
  size_t GetBuildKernelAsMicroseconds();
  size_t GetCopyBufferAsMicroseconds();
  size_t GetReadBufferAsMicroseconds();
  size_t GetEnqueueNDRangeAsMicroseconds();
  std::string GetOpenCLStatisticsAsString();
  float GetBandwidth();

  std::string main_result() const;
  std::string main_duration() const;
  std::map<std::string, float> results() const;
 private:
  void BuildProgram(const clpp::Program& program, const clpp::Device& device) override;
  void GetProfilingInfo();
  size_t GetProfilingInfoAsMicroseconds(clpp::Event event);
  std::vector<size_t> GetProfilingInfoAsMicroseconds(const std::vector<clpp::Event>& events);
  float ComputeBandwidthAsGBPS(size_t number_of_work_items, float seconds);

  mila::statistics::OpenCLStatistics device_statistics_;
  const std::string main_result_;
  const std::string main_duration_;
  std::map<std::string, float> results_;
  float bandwidth_;
};

}  // mila
#endif  // MILA_MEAN_SHIFT_PARALLEL_PROFILER_H_
