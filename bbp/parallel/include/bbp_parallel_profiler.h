#ifndef MILA_BBP_PARALLEL_PROFILER_H_
#define MILA_BBP_PARALLEL_PROFILER_H_

#include <chrono>
#include <map>
#include "bbp_parallel.h"

namespace mila {
namespace bbp {
namespace parallel {
class BBPProfiler : public BBP {
 public:
  BBPProfiler();
  BBPProfiler(float precision);
  BBPProfiler(size_t platform_id, size_t device_id);

  void Initialize() override;
  std::string Run(size_t number_of_digits, size_t starting_position) override;
  size_t GetBuildKernelAsMicroseconds();
  size_t GetReadBufferAsMicroseconds();
  size_t GetEnqueueNDRangeAsMicroseconds();

  std::string main_result() const;
  std::string main_duration() const;
  std::map<std::string, float> results() const;
 private:
  void BuildProgram(const clpp::Program& program, const clpp::Device& device) override;
  void GetProfilingInfo();

  const std::string main_result_;
  const std::string main_duration_;
  std::map<std::string, float> results_;
  DeviceStatistics device_statistics_;
};
};  // parallel
};  // bbp
}  // mila

#endif  // MILA_BBP_PARALLEL_PROFILER_H_
