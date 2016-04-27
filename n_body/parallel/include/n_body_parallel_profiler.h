#ifndef MILA_N_BODY_PARALLEL_PROFILER_H_
#define MILA_N_BODY_PARALLEL_PROFILER_H_

#include <chrono>
#include <map>

#include "n_body_parallel.h"

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

  std::string main_result() const;
  std::map<std::string, int64_t> results() const;
 private:
  const std::string main_result_;
  std::map<std::string, int64_t> results_;
};

}  // parallel
}  // nbody
}  // mila

#endif  // MILA_N_BODY_PARALLEL_PROFILER_H_
