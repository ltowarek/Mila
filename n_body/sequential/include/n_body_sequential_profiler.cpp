#include "n_body_sequential_profiler.h"

mila::SequentialNBodyProfiler::SequentialNBodyProfiler(std::unique_ptr<mila::SequentialNBody> n_body,
                                                       std::unique_ptr<mila::Profiler> profiler,
                                                       const std::shared_ptr<mila::Logger> logger)
    : n_body_(std::move(n_body)), profiler_(std::move(profiler)), logger_(logger) {
  InitResults();
}
mila::SequentialNBodyProfiler::~SequentialNBodyProfiler() {

}
mila::SequentialNBodyProfilingResults mila::SequentialNBodyProfiler::GetResults() const {
  return results_;
}
void mila::SequentialNBodyProfiler::UpdateParticles(const NBodyParameters &parameters,
                                                    const Vector2D &active_repulsion_force_position,
                                                    std::vector<Particle> &particles) {
  profiler_->Start("UpdateParticles");
  n_body_->UpdateParticles(parameters, active_repulsion_force_position, particles);
  profiler_->End("UpdateParticles");
  SetResultsAfterUpdateParticles(particles.size());
}
void mila::SequentialNBodyProfiler::InitResults() {
  results_.update_particles_duration = std::chrono::seconds(0);
  results_.particles_per_second = 0.0f;
}
void mila::SequentialNBodyProfiler::SetResultsAfterUpdateParticles(const size_t number_of_particles) {
  results_.update_particles_duration = profiler_->GetDuration("UpdateParticles");
  results_.particles_per_second = mila::utils::GetValuePerSecond(number_of_particles,
                                                                 results_.update_particles_duration);
}
mila::SequentialNBodyProfiler::SequentialNBodyProfiler(mila::SequentialNBodyProfiler &&profiler) :
    n_body_(std::move(profiler.n_body_)), profiler_(std::move(profiler.profiler_)), logger_(profiler.logger_) {

}
