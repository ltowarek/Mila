#include "n_body_interactive_view_profiler.hpp"

mila::NBodyInteractiveViewProfiler::NBodyInteractiveViewProfiler(std::unique_ptr<mila::NBodyInteractiveView> n_body,
                                                                 std::unique_ptr<mila::Profiler> profiler,
                                                                 const std::shared_ptr<mila::Logger> logger)
    : n_body_(std::move(n_body)), profiler_(std::move(profiler)), logger_(logger) {
}

mila::NBodyInteractiveViewProfiler::NBodyInteractiveViewProfiler(mila::NBodyInteractiveViewProfiler &&view)
    : n_body_(std::move(view.n_body_)), profiler_(std::move(view.profiler_)), logger_(view.logger_) {
}

void mila::NBodyInteractiveViewProfiler::Record(const mila::NBodyParameters &parameters,
                                                const int number_of_frames,
                                                mila::Vector2DFile &mouse_positions_file,
                                                mila::Vector2DFile &output_particles_file,
                                                std::vector<mila::Particle> &particles) {
  n_body_->Record(parameters, number_of_frames, mouse_positions_file, output_particles_file, particles);
}

bool mila::NBodyInteractiveViewProfiler::Replay(const mila::NBodyParameters &parameters,
                                                const mila::Vector2DFile &mouse_positions_file,
                                                const mila::Vector2DFile &reference_particles_file,
                                                std::vector<mila::Particle> &particles) {
  profiler_->Start("Replay");
  const auto output = n_body_->Replay(parameters, mouse_positions_file, reference_particles_file, particles);
  profiler_->End("Replay");
  SetResultsAfterReplay(mouse_positions_file.Read().size());
  return output;
}

mila::NBodyInteractiveViewProfilingResults mila::NBodyInteractiveViewProfiler::GetResults() const {
  return results_;
}

void mila::NBodyInteractiveViewProfiler::InitResults() {
  results_.replay_duration = std::chrono::seconds(0);
  results_.frames_per_second = 0.0f;
}

void mila::NBodyInteractiveViewProfiler::SetResultsAfterReplay(const size_t number_of_frames) {
  results_.replay_duration = profiler_->GetDuration("Replay");
  results_.frames_per_second = mila::utils::GetValuePerSecond(number_of_frames,
                                                              results_.replay_duration);
}
