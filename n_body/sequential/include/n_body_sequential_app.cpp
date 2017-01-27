#include "n_body_sequential_app.h"

mila::SequentialNBodyApp::SequentialNBodyApp(const std::shared_ptr<mila::Logger> logger) : logger_(logger) {

}
mila::SequentialNBodyApp::~SequentialNBodyApp() {

}
void mila::SequentialNBodyApp::Run(int argc, char **argv) const {
  const auto config = ParseCommandLine(argc, argv);
  PrintParameters(config);
  const auto raw_results = RunIterations(config);
  const auto prepared_results = PrepareResults(raw_results);
  PrintResultsStatistics(prepared_results);
}
mila::SequentialNBodyApp::Parameters mila::SequentialNBodyApp::ParseCommandLine(int argc, char **argv) const {
  if (argc < 3) {
    throw std::runtime_error("Wrong number of parameters: " + std::to_string(argc));
  }
  auto config = Parameters{0};
  config.number_of_particles = static_cast<size_t>(atoi(argv[1]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[2]));
  return config;
}
std::vector<mila::SequentialNBodyProfilingResults> mila::SequentialNBodyApp::RunIterations(
    const mila::SequentialNBodyApp::Parameters config) const {
  auto results = std::vector<mila::SequentialNBodyProfilingResults>();
  const auto warm_up_iterations = 1;
  for (size_t i = 0; i < config.number_of_iterations + warm_up_iterations; ++i) {
    logger_->Debug("Iteration: %d", i);

    auto n_body = std::unique_ptr<mila::SequentialNBody>(new mila::SequentialNBody(logger_));
    auto profiler = mila::ProfilerFactory().MakeChrono(logger_);
    auto n_body_profiler = std::unique_ptr<mila::SequentialNBodyProfiler>(new mila::SequentialNBodyProfiler(
        std::move(n_body),
        std::move(profiler),
        logger_));
    auto particles = mila::NBody::GenerateParticles(config.number_of_particles, 0.0f, 100.0f);
    const auto parameters = mila::NBodyParameters();
    n_body_profiler->UpdateParticles(parameters, Vector2D{0.0f, 0.0f}, particles);

    PrintResults(n_body_profiler->GetResults());

    if (i >= warm_up_iterations) {
      results.push_back(n_body_profiler->GetResults());
    }
  }
  return results;
}
mila::SequentialNBodyApp::Results mila::SequentialNBodyApp::PrepareResults(const std::vector<mila::SequentialNBodyProfilingResults> &raw_results) const {
  auto prepared_results = Results{};
  for (const auto &result : raw_results) {
    prepared_results.particles_per_second.push_back(result.particles_per_second);
    prepared_results.update_particles_duration.push_back(result.update_particles_duration.count());
  }
  return prepared_results;
}
void mila::SequentialNBodyApp::PrintParameters(const mila::SequentialNBodyApp::Parameters &config) const {
  logger_->Info("Number of particles: %d", config.number_of_particles);
  logger_->Info("Number of iterations: %d", config.number_of_iterations);
}
void mila::SequentialNBodyApp::PrintResults(const SequentialNBodyProfilingResults &results) const {
  logger_->Debug("Throughput: %f particles/s", results.particles_per_second);
  logger_->Debug("Update particles duration: %llu us", results.update_particles_duration);
}
void mila::SequentialNBodyApp::PrintResultsStatistics(const mila::SequentialNBodyApp::Results &results) const {
  mila::PrintResultStatistics("Throughput", "particles/s", results.particles_per_second, *logger_);
  mila::PrintResultStatistics("Update particles duration", "us", results.update_particles_duration, *logger_);
}
