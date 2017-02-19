#include "n_body_parallel_profiler.hpp"

mila::ParallelNBodyProfiler::ParallelNBodyProfiler(std::unique_ptr<mila::ParallelNBody> n_body,
                                                   std::unique_ptr<mila::Profiler> profiler,
                                                   const std::shared_ptr<mila::Logger> logger)
    : n_body_(std::move(n_body)), profiler_(std::move(profiler)), logger_(logger) {
  InitResults();
}

mila::ParallelNBodyProfiler::~ParallelNBodyProfiler() {
}

void mila::ParallelNBodyProfiler::Initialize() {
  profiler_->Start("Initialize");
  n_body_->Initialize();
  profiler_->End("Initialize");
  SetResultsAfterInitialize();
}

mila::ParallelNBodyProfilingResults mila::ParallelNBodyProfiler::GetResults() const {
  return results_;
}

void mila::ParallelNBodyProfiler::UpdateParticles(const NBodyParameters &parameters,
                                                  const Vector2D &active_repulsion_force_position,
                                                  std::vector<Particle> &particles) {
  profiler_->Start("UpdateParticles");
  n_body_->UpdateParticles(parameters, active_repulsion_force_position, particles);
  profiler_->End("UpdateParticles");
  SetResultsAfterUpdateParticles(particles.size());
}

void mila::ParallelNBodyProfiler::InitResults() {
  results_.update_particles_duration = std::chrono::seconds(0);
  results_.initialize_duration = std::chrono::seconds(0);
  results_.enqueue_nd_range_duration = std::chrono::seconds(0);
  results_.read_buffer_duration = std::chrono::seconds(0);
  results_.particles_per_second = 0.0f;
  results_.bandwidth = 0.0f;
}

void mila::ParallelNBodyProfiler::SetResultsAfterInitialize() {
  results_.initialize_duration = profiler_->GetDuration("Initialize");
}

void mila::ParallelNBodyProfiler::SetResultsAfterUpdateParticles(const size_t number_of_particles) {
  results_.update_particles_duration = profiler_->GetDuration("UpdateParticles");
  results_.enqueue_nd_range_duration =
      mila::GetProfilingInfo<std::chrono::microseconds>(n_body_->GetEvents().enqueue_nd_range);
  results_.read_buffer_duration =
      mila::GetProfilingInfo<std::chrono::microseconds>(n_body_->GetEvents().read_buffer);
  results_.particles_per_second = mila::GetValuePerSecond(number_of_particles,
                                                                 results_.update_particles_duration);
  results_.bandwidth = ComputeBandwidthAsGBPS(number_of_particles, results_.update_particles_duration.count());
}

float mila::ParallelNBodyProfiler::ComputeBandwidthAsGBPS(const size_t number_of_work_items,
                                                          const float microseconds) {
  auto gb_per_s = 0.0f;
  if (microseconds > 0) {
    const auto input_particles_bytes = sizeof(mila::Particle) * number_of_work_items * number_of_work_items;
    const auto output_particles_bytes = sizeof(mila::Particle) * number_of_work_items * 1;
    const auto parameters_bytes = sizeof(mila::NBodyParameters) * number_of_work_items * 1;
    const auto force_position_bytes = sizeof(cl_float2) * number_of_work_items * 1;
    const auto micro_to_giga = 1e3f;
    gb_per_s = (input_particles_bytes + output_particles_bytes + parameters_bytes + force_position_bytes) / microseconds
        / micro_to_giga;
  }
  return gb_per_s;
}

mila::ParallelNBodyProfiler::ParallelNBodyProfiler(mila::ParallelNBodyProfiler &&profiler) :
    n_body_(std::move(profiler.n_body_)), profiler_(std::move(profiler.profiler_)), logger_(profiler.logger_) {
}
