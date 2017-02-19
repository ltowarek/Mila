#include "n_body_parallel_app.hpp"

mila::ParallelNBodyApp::ParallelNBodyApp(const std::shared_ptr<mila::Logger> logger) : logger_(logger) {

}
mila::ParallelNBodyApp::~ParallelNBodyApp() {

}
void mila::ParallelNBodyApp::Run(int argc, char **argv) const {
  const auto config = ParseCommandLine(argc, argv);
  PrintParameters(config);
  const auto raw_results = RunIterations(config);
  const auto prepared_results = PrepareResults(raw_results);
  PrintResultsStatistics(prepared_results);
}
mila::ParallelNBodyApp::Parameters mila::ParallelNBodyApp::ParseCommandLine(int argc, char **argv) const {
  if (argc < 5) {
    throw std::runtime_error("Wrong number of parameters: " + std::to_string(argc));
  }
  auto config = Parameters{0};
  config.number_of_particles = static_cast<size_t>(atoi(argv[1]));
  config.platform_id = static_cast<size_t>(atoi(argv[2]));
  config.device_id = static_cast<size_t>(atoi(argv[3]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[4]));
  return config;
}
std::vector<mila::ParallelNBodyProfilingResults> mila::ParallelNBodyApp::RunIterations(
    const mila::ParallelNBodyApp::Parameters config) const {
  auto results = std::vector<mila::ParallelNBodyProfilingResults>();
  const auto warm_up_iterations = 1;
  for (size_t i = 0; i < config.number_of_iterations + warm_up_iterations; ++i) {
    logger_->Debug("Iteration: %d", i);

    auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(config.platform_id, config.device_id, logger_);

    if (i == 0) {
      logger_->Info("Platform name: %s", ocl_app->GetPlatformName().c_str());
      logger_->Info("Device name: %s", ocl_app->GetDeviceName().c_str());
    }

    auto n_body = std::unique_ptr<mila::ParallelNBody>(new mila::ParallelNBody(std::move(ocl_app), logger_));
    auto profiler = mila::ProfilerFactory().MakeChrono(logger_);
    auto n_body_profiler = std::unique_ptr<mila::ParallelNBodyProfiler>(new mila::ParallelNBodyProfiler(
        std::move(n_body),
        std::move(profiler),
        logger_));
    n_body_profiler->Initialize();

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
mila::ParallelNBodyApp::Results mila::ParallelNBodyApp::PrepareResults(const std::vector<mila::ParallelNBodyProfilingResults> &raw_results) const {
  auto prepared_results = Results{};
  for (const auto &result : raw_results) {
    prepared_results.particles_per_second.push_back(result.particles_per_second);
    prepared_results.update_particles_duration.push_back(result.update_particles_duration.count());
    prepared_results.initialize_duration.push_back(result.initialize_duration.count());
    prepared_results.read_buffer_duration.push_back(result.read_buffer_duration.count());
    prepared_results.enqueue_nd_range_duration.push_back(result.enqueue_nd_range_duration.count());
    prepared_results.particles_per_second.push_back(result.particles_per_second);
    prepared_results.bandwidth.push_back(result.bandwidth);
  }
  return prepared_results;
}
void mila::ParallelNBodyApp::PrintParameters(const mila::ParallelNBodyApp::Parameters &config) const {
  logger_->Info("Number of particles: %d", config.number_of_particles);
  logger_->Info("Number of iterations: %d", config.number_of_iterations);
  logger_->Info("Platform id: %d", config.platform_id);
  logger_->Info("Device id: %d", config.device_id);
}
void mila::ParallelNBodyApp::PrintResults(const ParallelNBodyProfilingResults &results) const {
  logger_->Debug("Bandwidth: %f GB/s", results.bandwidth);
  logger_->Debug("Throughput: %f particles/s", results.particles_per_second);
  logger_->Debug("Update particles duration: %llu us", results.update_particles_duration);
  logger_->Debug("Initialize duration: %llu us", results.initialize_duration);
  logger_->Debug("Enqueue ND range duration: %llu us", results.enqueue_nd_range_duration);
  logger_->Debug("Read buffer duration: %llu us", results.read_buffer_duration);
}
void mila::ParallelNBodyApp::PrintResultsStatistics(const mila::ParallelNBodyApp::Results &results) const {
  mila::PrintResultStatistics("Bandwidth", "GB/s", results.bandwidth, *logger_);
  mila::PrintResultStatistics("Throughput", "particles/s", results.particles_per_second, *logger_);
  mila::PrintResultStatistics("Initialize duration", "us", results.initialize_duration, *logger_);
  mila::PrintResultStatistics("Update particles duration", "us", results.update_particles_duration, *logger_);
  mila::PrintResultStatistics("Read buffer duration", "us", results.read_buffer_duration, *logger_);
  mila::PrintResultStatistics("Enqueue ND range duration", "us", results.enqueue_nd_range_duration, *logger_);
}
