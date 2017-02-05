#include "n_body_interactive_view_app.h"

mila::ParallelNBodyInteractiveViewApp::ParallelNBodyInteractiveViewApp(const std::shared_ptr<mila::Logger> logger)
    : logger_(logger) {

}

mila::ParallelNBodyInteractiveViewApp::~ParallelNBodyInteractiveViewApp() {

}

void mila::ParallelNBodyInteractiveViewApp::Run(int argc, char **argv) const {
  const auto config = ParseCommandLine(argc, argv);
  PrintParameters(config);
  const auto raw_results = RunIterations(config);
  if (config.action == "replay") {
    const auto prepared_results = PrepareResults(raw_results);
    PrintResultsStatistics(prepared_results);
  }
}

mila::ParallelNBodyInteractiveViewApp::Parameters mila::ParallelNBodyInteractiveViewApp::ParseCommandLine(
    int argc,
    char **argv) const {
  if (argc < 8) {
    throw std::runtime_error("Wrong number of parameters: " + std::to_string(argc));
  }
  auto config = Parameters();
  config.action = argv[1];
  config.number_of_particles = static_cast<size_t>(atoi(argv[2]));
  config.mouse_positions_file = argv[3];
  config.particles_file = argv[4];
  config.platform_id = static_cast<size_t>(atoi(argv[5]));
  config.device_id = static_cast<size_t>(atoi(argv[6]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[7]));
  return config;
}

std::vector<mila::NBodyInteractiveViewProfilingResults> mila::ParallelNBodyInteractiveViewApp::RunIterations(
    const mila::ParallelNBodyInteractiveViewApp::Parameters config) const {
  auto results = std::vector<mila::NBodyInteractiveViewProfilingResults>();
  const auto warm_up_iterations = 1;
  for (size_t i = 0; i < config.number_of_iterations + warm_up_iterations; ++i) {
    logger_->Debug("Iteration: %d", i);

    auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(config.platform_id, config.device_id, logger_);

    if (i == 0) {
      logger_->Info("Platform name: %s", ocl_app->GetPlatformName().c_str());
      logger_->Info("Device name: %s", ocl_app->GetDeviceName().c_str());
    }

    auto
        n_body = std::unique_ptr<mila::ParallelNBody>(new mila::ParallelNBody(std::move(ocl_app), logger_));
    n_body->Initialize();
    auto n_body_interactive_view =
        std::unique_ptr<mila::NBodyInteractiveView>(new mila::GenericNBodyInteractiveView(std::move(n_body), logger_));
    auto profiler = mila::ProfilerFactory().MakeChrono(logger_);
    auto n_body_profiler =
        std::unique_ptr<mila::NBodyInteractiveViewProfiler>(new mila::NBodyInteractiveViewProfiler(
            std::move(n_body_interactive_view),
            std::move(profiler),
            logger_));

    auto particles =
        mila::NBody::GenerateParticles(config.number_of_particles, 0.0f, 100.0f);
    auto mouse_positions_file = mila::Vector2DFile(config.mouse_positions_file);
    auto particles_file = mila::Vector2DFile(config.particles_file);
    const auto parameters = mila::NBodyParameters();

    if (config.action == "replay") {
      n_body_profiler->Replay(parameters,
                              mouse_positions_file,
                              particles_file,
                              particles);

      PrintResults(n_body_profiler->GetResults());

      if (i >= warm_up_iterations) {
        results.push_back(n_body_profiler->GetResults());
      }
    } else {
      n_body_profiler->Record(parameters,
                              -1,
                              mouse_positions_file,
                              particles_file,
                              particles);
    }
  }
  return results;
}

mila::ParallelNBodyInteractiveViewApp::Results mila::ParallelNBodyInteractiveViewApp::PrepareResults(const std::vector<
    mila::NBodyInteractiveViewProfilingResults> &raw_results) const {
  auto prepared_results = Results{};
  for (const auto &result : raw_results) {
    prepared_results.frames_per_second.push_back(result.frames_per_second);
    prepared_results.replay_duration.push_back(result.replay_duration.count());
  }
  return prepared_results;
}

void mila::ParallelNBodyInteractiveViewApp::PrintParameters(const mila::ParallelNBodyInteractiveViewApp::Parameters &config) const {
  logger_->Info("Mouse positions file: %s", config.mouse_positions_file.c_str());
  logger_->Info("Particles file: %s", config.particles_file.c_str());
  logger_->Info("Number of iterations: %d", config.number_of_iterations);
  logger_->Info("Platform id: %d", config.platform_id);
  logger_->Info("Device id: %d", config.device_id);
}

void mila::ParallelNBodyInteractiveViewApp::PrintResults(const NBodyInteractiveViewProfilingResults &results) const {
  logger_->Debug("Throughput: %f frames/s", results.frames_per_second);
  logger_->Debug("Replay duration: %llu us", results.replay_duration);
}

void mila::ParallelNBodyInteractiveViewApp::PrintResultsStatistics(const mila::ParallelNBodyInteractiveViewApp::Results &results) const {
  mila::PrintResultStatistics("Throughput", "frames/s", results.frames_per_second, *logger_);
  mila::PrintResultStatistics("Replay duration",
                              "us",
                              results.replay_duration,
                              *logger_);
}

mila::SequentialNBodyInteractiveViewApp::SequentialNBodyInteractiveViewApp(const std::shared_ptr<mila::Logger> logger)
    : logger_(logger) {

}

mila::SequentialNBodyInteractiveViewApp::~SequentialNBodyInteractiveViewApp() {

}

void mila::SequentialNBodyInteractiveViewApp::Run(int argc, char **argv) const {
  const auto config = ParseCommandLine(argc, argv);
  PrintParameters(config);
  const auto raw_results = RunIterations(config);
  if (config.action == "replay") {
    const auto prepared_results = PrepareResults(raw_results);
    PrintResultsStatistics(prepared_results);
  }
}

mila::SequentialNBodyInteractiveViewApp::Parameters mila::SequentialNBodyInteractiveViewApp::ParseCommandLine(
    int argc,
    char **argv) const {
  if (argc < 6) {
    throw std::runtime_error("Wrong number of parameters: " + std::to_string(argc));
  }
  auto config = Parameters();
  config.action = argv[1];
  config.number_of_particles = static_cast<size_t>(atoi(argv[2]));
  config.mouse_positions_file = argv[3];
  config.particles_file = argv[4];
  config.number_of_iterations = static_cast<size_t>(atoi(argv[5]));
  return config;
}

std::vector<mila::NBodyInteractiveViewProfilingResults> mila::SequentialNBodyInteractiveViewApp::RunIterations(
    const mila::SequentialNBodyInteractiveViewApp::Parameters config) const {
  auto results = std::vector<mila::NBodyInteractiveViewProfilingResults>();
  const auto warm_up_iterations = 1;
  for (size_t i = 0; i < config.number_of_iterations + warm_up_iterations; ++i) {
    logger_->Debug("Iteration: %d", i);

    auto
        n_body = std::unique_ptr<mila::SequentialNBody>(new mila::SequentialNBody(logger_));
    auto n_body_interactive_view =
        std::unique_ptr<mila::NBodyInteractiveView>(new mila::GenericNBodyInteractiveView(std::move(n_body), logger_));
    auto profiler = mila::ProfilerFactory().MakeChrono(logger_);
    auto n_body_profiler =
        std::unique_ptr<mila::NBodyInteractiveViewProfiler>(new mila::NBodyInteractiveViewProfiler(
            std::move(n_body_interactive_view),
            std::move(profiler),
            logger_));

    auto particles =
        mila::NBody::GenerateParticles(config.number_of_particles, 0.0f, 100.0f);
    auto mouse_positions_file = mila::Vector2DFile(config.mouse_positions_file);
    auto particles_file = mila::Vector2DFile(config.particles_file);
    const auto parameters = mila::NBodyParameters();

    if (config.action == "replay") {
      n_body_profiler->Replay(parameters,
                              mouse_positions_file,
                              particles_file,
                              particles);

      PrintResults(n_body_profiler->GetResults());

      if (i >= warm_up_iterations) {
        results.push_back(n_body_profiler->GetResults());
      }
    } else {
      n_body_profiler->Record(parameters,
                              -1,
                              mouse_positions_file,
                              particles_file,
                              particles);
    }
  }
  return results;
}

mila::SequentialNBodyInteractiveViewApp::Results mila::SequentialNBodyInteractiveViewApp::PrepareResults(const std::vector<
    mila::NBodyInteractiveViewProfilingResults> &raw_results) const {
  auto prepared_results = Results{};
  for (const auto &result : raw_results) {
    prepared_results.frames_per_second.push_back(result.frames_per_second);
    prepared_results.replay_duration.push_back(result.replay_duration.count());
  }
  return prepared_results;
}

void mila::SequentialNBodyInteractiveViewApp::PrintParameters(const mila::SequentialNBodyInteractiveViewApp::Parameters &config) const {
  logger_->Info("Mouse positions file: %s", config.mouse_positions_file.c_str());
  logger_->Info("Particles file: %s", config.particles_file.c_str());
  logger_->Info("Number of iterations: %d", config.number_of_iterations);
}

void mila::SequentialNBodyInteractiveViewApp::PrintResults(const NBodyInteractiveViewProfilingResults &results) const {
  logger_->Debug("Throughput: %f frames/s", results.frames_per_second);
  logger_->Debug("Replay duration: %llu us", results.replay_duration);
}

void mila::SequentialNBodyInteractiveViewApp::PrintResultsStatistics(const mila::SequentialNBodyInteractiveViewApp::Results &results) const {
  mila::PrintResultStatistics("Throughput", "frames/s", results.frames_per_second, *logger_);
  mila::PrintResultStatistics("Replay duration",
                              "us",
                              results.replay_duration,
                              *logger_);
}
