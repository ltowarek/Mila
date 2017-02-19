#include "mean_shift_image_processing_app.hpp"

mila::SequentialMeanShiftImageProcessingApp::SequentialMeanShiftImageProcessingApp(const std::shared_ptr<mila::Logger> logger)
    : logger_(logger) {

}
mila::SequentialMeanShiftImageProcessingApp::~SequentialMeanShiftImageProcessingApp() {

}
void mila::SequentialMeanShiftImageProcessingApp::Run(int argc, char **argv) const {
  const auto config = ParseCommandLine(argc, argv);
  PrintParameters(config);
  const auto raw_results = RunIterations(config);
  const auto prepared_results = PrepareResults(raw_results);
  PrintResultsStatistics(prepared_results);
}
mila::SequentialMeanShiftImageProcessingApp::Parameters mila::SequentialMeanShiftImageProcessingApp::ParseCommandLine(
    int argc,
    char **argv) const {
  if (argc < 5) {
    throw std::runtime_error("Wrong number of parameters: " + std::to_string(argc));
  }
  auto config = Parameters();
  config.input_file = std::string(argv[1]);
  config.output_file = std::string(argv[2]);
  config.bandwidth = static_cast<float>(atof(argv[3]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[4]));
  return config;
}
std::vector<mila::MeanShiftImageProcessingProfilingResults> mila::SequentialMeanShiftImageProcessingApp::RunIterations(
    const mila::SequentialMeanShiftImageProcessingApp::Parameters config) const {
  auto results = std::vector<mila::MeanShiftImageProcessingProfilingResults>();
  const auto warm_up_iterations = 1;
  for (size_t i = 0; i < config.number_of_iterations + warm_up_iterations; ++i) {
    logger_->Debug("Iteration: %d", i);

    auto mean_shift = std::unique_ptr<mila::MeanShift>(new mila::SequentialMeanShift(logger_));
    auto mean_shift_image_processing =
        std::unique_ptr<mila::MeanShiftImageProcessing>(new mila::GenericMeanShiftImageProcessing(std::move(mean_shift),
                                                                                                  logger_));
    auto profiler = mila::ProfilerFactory().MakeChrono(logger_);
    auto mean_shift_profiler =
        std::unique_ptr<mila::MeanShiftImageProcessingProfiler>(new mila::MeanShiftImageProcessingProfiler(
            std::move(mean_shift_image_processing),
            std::move(profiler),
            logger_));
    mean_shift_profiler->Run(config.input_file, config.output_file, config.bandwidth);

    PrintResults(mean_shift_profiler->GetResults());

    if (i >= warm_up_iterations) {
      results.push_back(mean_shift_profiler->GetResults());
    }
  }
  return results;
}
mila::SequentialMeanShiftImageProcessingApp::Results mila::SequentialMeanShiftImageProcessingApp::PrepareResults(const std::vector<
    mila::MeanShiftImageProcessingProfilingResults> &raw_results) const {
  auto prepared_results = Results{};
  for (const auto &result : raw_results) {
    prepared_results.pixels_per_second.push_back(result.pixels_per_second);
    prepared_results.mean_shift_image_processing_duration.push_back(result.mean_shift_image_processing_duration.count());
  }
  return prepared_results;
}
void mila::SequentialMeanShiftImageProcessingApp::PrintParameters(const mila::SequentialMeanShiftImageProcessingApp::Parameters &config) const {
  logger_->Info("Input file: %s", config.input_file.c_str());
  logger_->Info("Output file: %s", config.output_file.c_str());
  logger_->Info("Bandwidth: %f", config.bandwidth);
  logger_->Info("Number of iterations: %d", config.number_of_iterations);
}
void mila::SequentialMeanShiftImageProcessingApp::PrintResults(const MeanShiftImageProcessingProfilingResults &results) const {
  logger_->Debug("Throughput: %f pixels/s", results.pixels_per_second);
  logger_->Debug("Mean shift image processing duration: %llu us", results.mean_shift_image_processing_duration);
}
void mila::SequentialMeanShiftImageProcessingApp::PrintResultsStatistics(const mila::SequentialMeanShiftImageProcessingApp::Results &results) const {
  mila::PrintResultStatistics("Throughput", "pixels/s", results.pixels_per_second, *logger_);
  mila::PrintResultStatistics("Mean shift image processing duration",
                              "us",
                              results.mean_shift_image_processing_duration,
                              *logger_);
}
mila::ParallelMeanShiftImageProcessingApp::ParallelMeanShiftImageProcessingApp(const std::shared_ptr<mila::Logger> logger)
    : logger_(logger) {

}
mila::ParallelMeanShiftImageProcessingApp::~ParallelMeanShiftImageProcessingApp() {

}
void mila::ParallelMeanShiftImageProcessingApp::Run(int argc, char **argv) const {
  const auto config = ParseCommandLine(argc, argv);
  PrintParameters(config);
  const auto raw_results = RunIterations(config);
  const auto prepared_results = PrepareResults(raw_results);
  PrintResultsStatistics(prepared_results);
}
mila::ParallelMeanShiftImageProcessingApp::Parameters mila::ParallelMeanShiftImageProcessingApp::ParseCommandLine(
    int argc,
    char **argv) const {
  if (argc < 7) {
    throw std::runtime_error("Wrong number of parameters: " + std::to_string(argc));
  }
  auto config = Parameters();
  config.input_file = std::string(argv[1]);
  config.output_file = std::string(argv[2]);
  config.bandwidth = static_cast<float>(atof(argv[3]));
  config.platform_id = static_cast<size_t>(atoi(argv[4]));
  config.device_id = static_cast<size_t>(atoi(argv[5]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[6]));
  return config;
}
std::vector<mila::MeanShiftImageProcessingProfilingResults> mila::ParallelMeanShiftImageProcessingApp::RunIterations(
    const mila::ParallelMeanShiftImageProcessingApp::Parameters config) const {
  auto results = std::vector<mila::MeanShiftImageProcessingProfilingResults>();
  const auto warm_up_iterations = 1;
  for (size_t i = 0; i < config.number_of_iterations + warm_up_iterations; ++i) {
    logger_->Debug("Iteration: %d", i);

    auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(config.platform_id, config.device_id, logger_);

    if (i == 0) {
      logger_->Info("Platform name: %s", ocl_app->GetPlatformName().c_str());
      logger_->Info("Device name: %s", ocl_app->GetDeviceName().c_str());
    }

    auto
        mean_shift = std::unique_ptr<mila::ParallelMeanShift>(new mila::ParallelMeanShift(std::move(ocl_app), logger_));
    mean_shift->Initialize();
    auto mean_shift_image_processing =
        std::unique_ptr<mila::MeanShiftImageProcessing>(new mila::GenericMeanShiftImageProcessing(std::move(mean_shift),
                                                                                                  logger_));
    auto profiler = mila::ProfilerFactory().MakeChrono(logger_);
    auto mean_shift_profiler =
        std::unique_ptr<mila::MeanShiftImageProcessingProfiler>(new mila::MeanShiftImageProcessingProfiler(
            std::move(mean_shift_image_processing),
            std::move(profiler),
            logger_));
    mean_shift_profiler->Run(config.input_file, config.output_file, config.bandwidth);

    PrintResults(mean_shift_profiler->GetResults());

    if (i >= warm_up_iterations) {
      results.push_back(mean_shift_profiler->GetResults());
    }
  }
  return results;
}
mila::ParallelMeanShiftImageProcessingApp::Results mila::ParallelMeanShiftImageProcessingApp::PrepareResults(const std::vector<
    mila::MeanShiftImageProcessingProfilingResults> &raw_results) const {
  auto prepared_results = Results{};
  for (const auto &result : raw_results) {
    prepared_results.pixels_per_second.push_back(result.pixels_per_second);
    prepared_results.mean_shift_image_processing_duration.push_back(result.mean_shift_image_processing_duration.count());
  }
  return prepared_results;
}
void mila::ParallelMeanShiftImageProcessingApp::PrintParameters(const mila::ParallelMeanShiftImageProcessingApp::Parameters &config) const {
  logger_->Info("Input file: %s", config.input_file.c_str());
  logger_->Info("Output file: %s", config.output_file.c_str());
  logger_->Info("Bandwidth: %f", config.bandwidth);
  logger_->Info("Number of iterations: %d", config.number_of_iterations);
  logger_->Info("Platform id: %d", config.platform_id);
  logger_->Info("Device id: %d", config.device_id);
}
void mila::ParallelMeanShiftImageProcessingApp::PrintResults(const MeanShiftImageProcessingProfilingResults &results) const {
  logger_->Debug("Throughput: %f pixels/s", results.pixels_per_second);
  logger_->Debug("Mean shift image processing duration: %llu us", results.mean_shift_image_processing_duration);
}
void mila::ParallelMeanShiftImageProcessingApp::PrintResultsStatistics(const mila::ParallelMeanShiftImageProcessingApp::Results &results) const {
  mila::PrintResultStatistics("Throughput", "pixels/s", results.pixels_per_second, *logger_);
  mila::PrintResultStatistics("Mean shift image processing duration",
                              "us",
                              results.mean_shift_image_processing_duration,
                              *logger_);
}
