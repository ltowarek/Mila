#ifndef MILA_N_BODY_PARALLEL_PROFILER_H_
#define MILA_N_BODY_PARALLEL_PROFILER_H_

#include <chrono>
#include <map>

#include "n_body_parallel.h"
#include "statistics.h"

namespace mila {
namespace nbody {
namespace parallel {

class NBodyParallelWithInputFileProfiler: public NBodyParallelWithInputFile {
 public:
  NBodyParallelWithInputFileProfiler();
  NBodyParallelWithInputFileProfiler(int number_of_particles, size_t platform_id, size_t device_id);
  NBodyParallelWithInputFileProfiler(float active_repulsion_force,
                                     float active_repulsion_min_distance,
                                     float passive_repulsion_force,
                                     float passive_repulsion_min_distance,
                                     float damping_force,
                                     float central_force,
                                     cl_float2 center,
                                     int number_of_particles,
                                     float min_position,
                                     float max_position,
                                     size_t platform_id,
                                     size_t device_id);

  void Run(const std::string &input_file) override;
  size_t GetBuildKernelAsMicroseconds();
  size_t GetReadBufferAsMicroseconds();
  size_t GetEnqueueNDRangeAsMicroseconds();
  std::string GetOpenCLStatisticsAsString();
  float GetBandwidth();

  std::string main_result() const;
  std::string main_duration() const;
  std::map<std::string, float> results() const;
 private:
  virtual void BuildProgram(const clpp::Program& program, const clpp::Device& device, const std::string& build_options) override;
  void GetProfilingInfo();
  size_t GetProfilingInfoAsMicroseconds(clpp::Event);
  float ComputeBandwidthAsGBPS(size_t number_of_work_items, float seconds);

  mila::statistics::OpenCLStatistics device_statistics_;
  const std::string main_result_;
  const std::string main_duration_;
  std::map<std::string, float> results_;
  float bandwidth_;
};

}  // parallel
}  // nbody
}  // mila

#endif  // MILA_N_BODY_PARALLEL_PROFILER_H_
