#ifndef MILA_N_BODY_PARALLEL_PROFILER_H_
#define MILA_N_BODY_PARALLEL_PROFILER_H_

#include "n_body_parallel.h"
#include "statistics.h"
#include "utils.h"
#include "profiler.h"

namespace mila {
struct ParallelNBodyProfilingResults {
  std::chrono::microseconds update_particles_duration;
  std::chrono::microseconds initialize_duration;
  std::chrono::microseconds enqueue_nd_range_duration;
  std::chrono::microseconds read_buffer_duration;
  float particles_per_second;
  float bandwidth;
};
class ParallelNBodyProfiler : public NBody {
 public:
  ParallelNBodyProfiler(std::unique_ptr<mila::ParallelNBody> n_body,
                        std::unique_ptr<mila::Profiler> profiler,
                        const std::shared_ptr<mila::Logger> logger);
  ParallelNBodyProfiler(ParallelNBodyProfiler &&profiler);
  virtual ~ParallelNBodyProfiler();

  virtual void UpdateParticles(const NBodyParameters &parameters,
                               const Vector2D &active_repulsion_force_position,
                               std::vector<Particle> &particles);
  virtual void Initialize();

  ParallelNBodyProfilingResults GetResults() const;
 private:
  std::unique_ptr<mila::ParallelNBody> n_body_;
  std::unique_ptr<mila::Profiler> profiler_;
  std::shared_ptr<mila::Logger> logger_;
  ParallelNBodyProfilingResults results_;

  float ComputeBandwidthAsGBPS(const size_t number_of_work_items, const float seconds);
  void SetResultsAfterUpdateParticles(const size_t number_of_particles);
  void SetResultsAfterInitialize();
  void InitResults();
};
}  // mila
#endif  // MILA_N_BODY_PARALLEL_PROFILER_H_
