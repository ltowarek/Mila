#ifndef MILA_N_BODY_SEQUENTIAL_PROFILER_H_
#define MILA_N_BODY_SEQUENTIAL_PROFILER_H_

#include <chrono>
#include <map>

#include "n_body_sequential.h"

namespace mila {
namespace nbody {
namespace sequential {

class NBodySequentialWithInputFileProfiler: public NBodySequentialWithInputFile {
 public:
  NBodySequentialWithInputFileProfiler();
  NBodySequentialWithInputFileProfiler(int number_of_particles);
  NBodySequentialWithInputFileProfiler(float active_repulsion_force_,
                               float active_repulsion_min_distance_,
                               float passive_repulsion_force_,
                               float passive_repulsion_min_distance_,
                               float damping_force_,
                               float central_force_,
                               Vector2D center_,
                               int number_of_particles_,
                               float min_position_,
                               float max_position_);

  void Run(const std::string &input_file) override;

  std::string main_result() const;
  std::map<std::string, int64_t> results() const;
 private:
  const std::string main_result_;
  std::map<std::string, int64_t> results_;
};

}  // sequential
}  // nbody
}  // mila

#endif  // MILA_N_BODY_SEQUENTIAL_PROFILER_H_
