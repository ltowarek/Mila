#ifndef MILA_N_BODY_INTERACTIVE_VIEW_PROFILER_H
#define MILA_N_BODY_INTERACTIVE_VIEW_PROFILER_H

#include "profiler.hpp"
#include "n_body_interactive_view.hpp"

namespace mila {
struct NBodyInteractiveViewProfilingResults {
  std::chrono::microseconds replay_duration;
  float frames_per_second;
};

class NBodyInteractiveViewProfiler {
 public:
  NBodyInteractiveViewProfiler(std::unique_ptr<mila::NBodyInteractiveView> n_body,
                               std::unique_ptr<mila::Profiler> profiler,
                               const std::shared_ptr<mila::Logger> logger);
  NBodyInteractiveViewProfiler(NBodyInteractiveViewProfiler &&view);

  void Record(const mila::NBodyParameters &parameters,
              const int number_of_frames,
              mila::Vector2DFile &mouse_positions_file,
              mila::Vector2DFile &output_particles_file,
              std::vector<Particle> &particles);
  bool Replay(const mila::NBodyParameters &parameters,
              const mila::Vector2DFile &mouse_positions_file,
              const mila::Vector2DFile &reference_particles_file,
              std::vector<Particle> &particles);

  NBodyInteractiveViewProfilingResults GetResults() const;
 private:
  std::unique_ptr<mila::NBodyInteractiveView> n_body_;
  const std::shared_ptr<mila::Logger> logger_;
  std::unique_ptr<mila::Profiler> profiler_;
  NBodyInteractiveViewProfilingResults results_;

  void InitResults();
  void SetResultsAfterReplay(const size_t number_of_frames);
};
}  // mila
#endif  // MILA_N_BODY_INTERACTIVE_VIEW_PROFILER_H
