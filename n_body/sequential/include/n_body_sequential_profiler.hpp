#ifndef MILA_N_BODY_SEQUENTIAL_PROFILER_HPP
#define MILA_N_BODY_SEQUENTIAL_PROFILER_HPP

#include "n_body_sequential.hpp"
#include "profiler.hpp"
#include "utils.hpp"

namespace mila {
struct SequentialNBodyProfilingResults {
  std::chrono::microseconds update_particles_duration;
  float particles_per_second;
};
class SequentialNBodyProfiler : public NBody {
 public:
  SequentialNBodyProfiler(std::unique_ptr<mila::SequentialNBody> n_body,
                          std::unique_ptr<mila::Profiler> profiler,
                          const std::shared_ptr<mila::Logger> logger);
  SequentialNBodyProfiler(SequentialNBodyProfiler &&profiler);
  virtual ~SequentialNBodyProfiler();

  virtual void UpdateParticles(const NBodyParameters &parameters,
                               const Vector2D &active_repulsion_force_position,
                               std::vector<Particle> &particles);

  SequentialNBodyProfilingResults GetResults() const;
 private:
  std::unique_ptr<mila::SequentialNBody> n_body_;
  std::unique_ptr<mila::Profiler> profiler_;
  std::shared_ptr<mila::Logger> logger_;
  SequentialNBodyProfilingResults results_;

  void SetResultsAfterUpdateParticles(const size_t number_of_particles);
  void InitResults();
};
}  // mila
#endif  // MILA_N_BODY_SEQUENTIAL_PROFILER_HPP
