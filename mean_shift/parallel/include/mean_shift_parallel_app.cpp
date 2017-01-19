#include "mean_shift_parallel_app.h"

mila::ParallelMeanShiftApp::ParallelMeanShiftApp(const std::shared_ptr<mila::Logger> logger) : logger_(logger) {

}
mila::ParallelMeanShiftApp::~ParallelMeanShiftApp() {

}
void mila::ParallelMeanShiftApp::Run(int argc, char **argv) const {
  const auto config = ParseCommandLine(argc, argv);
  PrintParameters(config);
  const auto raw_results = RunIterations(config);
  const auto prepared_results = PrepareResults(raw_results);
  PrintResultsStatistics(prepared_results);
}
mila::ParallelMeanShiftApp::Parameters mila::ParallelMeanShiftApp::ParseCommandLine(int argc, char **argv) const {
  if (argc < 7) {
    throw std::runtime_error("Wrong number of parameters: " + std::to_string(argc));
  }
  auto i = 1;
  auto config = Parameters();
  const auto number_of_points = static_cast<size_t>(atoi(argv[i++]));
  const auto number_of_dimensions = 4;
  for (; i < number_of_dimensions * number_of_points;) {
    auto point = Point{0};
    point.x = static_cast<float>(atof(argv[i++]));
    point.y = static_cast<float>(atof(argv[i++]));
    point.z = static_cast<float>(atof(argv[i++]));
    point.w = static_cast<float>(atof(argv[i++]));
    config.points.push_back(point);
  }
  config.bandwidth = static_cast<float>(atof(argv[i++]));
  config.platform_id = static_cast<size_t>(atoi(argv[i++]));
  config.device_id = static_cast<size_t>(atoi(argv[i++]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[i]));
  return config;
}
std::vector<mila::ParallelMeanShiftProfilingResults> mila::ParallelMeanShiftApp::RunIterations(
    const mila::ParallelMeanShiftApp::Parameters config) const {
  auto results = std::vector<mila::ParallelMeanShiftProfilingResults>();
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
    auto profiler = mila::ProfilerFactory().MakeChrono(logger_);
    auto mean_shift_profiler = std::unique_ptr<mila::ParallelMeanShiftProfiler>(new mila::ParallelMeanShiftProfiler(
        std::move(mean_shift),
        std::move(profiler),
        logger_));
    mean_shift_profiler->Initialize();
    auto points = mean_shift_profiler->Run(config.points, config.bandwidth);
    auto points_str = mila::to_string(points);

    if (i == 0) {
      logger_->Info("Output:\n%s", points_str.c_str());
    } else {
      logger_->Debug("Output:\n%s", points_str.c_str());
    }

    PrintResults(mean_shift_profiler->GetResults());

    if (i >= warm_up_iterations) {
      results.push_back(mean_shift_profiler->GetResults());
    }
  }
  return results;
}
mila::ParallelMeanShiftApp::Results mila::ParallelMeanShiftApp::PrepareResults(const std::vector<mila::ParallelMeanShiftProfilingResults> &raw_results) const {
  auto prepared_results = Results{};
  for (const auto &result : raw_results) {
    prepared_results.mean_shift_duration.push_back(result.mean_shift_duration.count());
    prepared_results.initialize_duration.push_back(result.initialize_duration.count());
    prepared_results.read_buffer_with_output_duration.push_back(result.read_buffer_with_output_duration.count());

    prepared_results.read_buffer_with_distances_durations.push_back(mila::utils::Sum(mila::utils::ExtractTimeCountFromVector(
        result.read_buffer_with_distances_durations)));
    prepared_results.copy_buffer_durations.push_back(mila::utils::Sum(mila::utils::ExtractTimeCountFromVector(result.copy_buffer_durations)));
    prepared_results.enqueue_nd_range_durations.push_back(mila::utils::Sum(mila::utils::ExtractTimeCountFromVector(
        result.enqueue_nd_range_durations)));

    auto tmp_values = mila::utils::ExtractTimeCountFromVector(result.read_buffer_with_distances_durations);
    prepared_results.read_buffer_with_distances_duration.insert(prepared_results.read_buffer_with_distances_duration.end(),
                                                                tmp_values.begin(),
                                                                tmp_values.end());
    tmp_values = mila::utils::ExtractTimeCountFromVector(result.copy_buffer_durations);
    prepared_results.copy_buffer_duration.insert(prepared_results.copy_buffer_duration.end(),
                                                 tmp_values.begin(),
                                                 tmp_values.end());
    tmp_values = mila::utils::ExtractTimeCountFromVector(result.enqueue_nd_range_durations);
    prepared_results.enqueue_nd_range_duration.insert(prepared_results.enqueue_nd_range_duration.end(),
                                                      tmp_values.begin(),
                                                      tmp_values.end());

    prepared_results.points_per_second.push_back(result.points_per_second);
    prepared_results.bandwidth.push_back(result.bandwidth);
  }
  return prepared_results;
}
void mila::ParallelMeanShiftApp::PrintParameters(const mila::ParallelMeanShiftApp::Parameters &config) const {
  logger_->Info("Points:\n%s", mila::to_string(config.points).c_str());
  logger_->Info("Bandwidth: %f", config.bandwidth);
  logger_->Info("Number of iterations: %d", config.number_of_iterations);
  logger_->Info("Platform id: %d", config.platform_id);
  logger_->Info("Device id: %d", config.device_id);
}
void mila::ParallelMeanShiftApp::PrintResults(const ParallelMeanShiftProfilingResults &results) const {
  logger_->Debug("Bandwidth: %f GB/s", results.bandwidth);
  logger_->Debug("Throughput: %f points/s", results.points_per_second);
  logger_->Debug("Mean shift duration: %llu us", results.mean_shift_duration);
  logger_->Debug("Initialize duration: %llu us", results.initialize_duration);
  logger_->Debug("Read buffer with output duration: %llu us", results.read_buffer_with_output_duration);
  logger_->Debug("Read buffer with distances duration:\n%s",
                 mila::to_string(results.read_buffer_with_distances_durations).c_str());
  logger_->Debug("Copy buffer duration:\n%s", mila::to_string(results.copy_buffer_durations).c_str());
  logger_->Debug("Enqueue ND range duration:\n%s", mila::to_string(results.enqueue_nd_range_durations).c_str());
}
void mila::ParallelMeanShiftApp::PrintResultsStatistics(const mila::ParallelMeanShiftApp::Results &results) const {
  mila::PrintResultStatistics("Bandwidth", "GB/s", results.bandwidth, *logger_);
  mila::PrintResultStatistics("Throughput", "points/s", results.points_per_second, *logger_);
  mila::PrintResultStatistics("Initialize duration", "us", results.initialize_duration, *logger_);
  mila::PrintResultStatistics("Mean shift duration", "us", results.mean_shift_duration, *logger_);
  mila::PrintResultStatistics("Read buffer with output duration",
                              "us",
                              results.read_buffer_with_output_duration,
                              *logger_);
  mila::PrintResultStatistics("Read buffer with distances durations",
                              "us",
                              results.read_buffer_with_distances_durations,
                              *logger_);
  mila::PrintResultStatistics("Single read buffer with distances duration",
                              "us",
                              results.read_buffer_with_distances_duration,
                              *logger_);
  mila::PrintResultStatistics("Copy buffer durations", "us", results.copy_buffer_durations, *logger_);
  mila::PrintResultStatistics("Single copy buffer duration", "us", results.copy_buffer_duration, *logger_);
  mila::PrintResultStatistics("Enqueue ND range durations", "us", results.enqueue_nd_range_durations, *logger_);
  mila::PrintResultStatistics("Single enqueue ND range duration", "us", results.enqueue_nd_range_duration, *logger_);
}
