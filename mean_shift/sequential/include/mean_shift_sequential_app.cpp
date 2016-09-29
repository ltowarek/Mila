#include "mean_shift_sequential_app.h"

mila::SequentialMeanShiftApp::SequentialMeanShiftApp(const std::shared_ptr<mila::Logger> logger) : logger_(logger) {

}
mila::SequentialMeanShiftApp::~SequentialMeanShiftApp() {

}
void mila::SequentialMeanShiftApp::Run(int argc, char **argv) const {
  const auto config = ParseCommandLine(argc, argv);
  PrintParameters(config);
  const auto raw_results = RunIterations(config);
  const auto prepared_results = PrepareResults(raw_results);
  PrintResultsStatistics(prepared_results);
}
mila::SequentialMeanShiftApp::Parameters mila::SequentialMeanShiftApp::ParseCommandLine(int argc, char **argv) const {
  if (argc < 5) {
    throw std::runtime_error("Wrong number of parameters: " + std::to_string(argc));
  }
  auto i = 1;
  auto config = Parameters();
  const auto number_of_points = static_cast<size_t>(atoi(argv[i++]));
  const auto number_of_dimensions = 4;
  for (;i < number_of_dimensions * number_of_points;) {
    auto point = Point{0};
    point.x = static_cast<float>(atof(argv[i++]));
    point.y = static_cast<float>(atof(argv[i++]));
    point.z = static_cast<float>(atof(argv[i++]));
    point.w = static_cast<float>(atof(argv[i++]));
    config.points.push_back(point);
  }
  config.bandwidth = static_cast<float>(atof(argv[i++]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[i++]));
  return config;
}
std::vector<mila::SequentialMeanShiftProfilingResults> mila::SequentialMeanShiftApp::RunIterations(
    const mila::SequentialMeanShiftApp::Parameters config) const {
  auto results = std::vector<mila::SequentialMeanShiftProfilingResults>();
  const auto warm_up_iterations = 1;
  for (size_t i = 0; i < config.number_of_iterations + warm_up_iterations; ++i) {
    logger_->Debug("Iteration: %d", i);

    auto mean_shift = std::unique_ptr<mila::SequentialMeanShift>(new mila::SequentialMeanShift(logger_));
    auto profiler = mila::ProfilerFactory().MakeChrono(logger_);
    auto mean_shift_profiler = std::unique_ptr<mila::SequentialMeanShiftProfiler>(new mila::SequentialMeanShiftProfiler(std::move(mean_shift), std::move(profiler), logger_));
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
mila::SequentialMeanShiftApp::Results mila::SequentialMeanShiftApp::PrepareResults(const std::vector <mila::SequentialMeanShiftProfilingResults> &raw_results) const {
  auto prepared_results = Results{};
  for (const auto& result : raw_results) {
    prepared_results.points_per_second.push_back(result.points_per_second);
    prepared_results.mean_shift_duration.push_back(result.mean_shift_duration.count());
  }
  return prepared_results;
}
void mila::SequentialMeanShiftApp::PrintParameters(const mila::SequentialMeanShiftApp::Parameters &config) const {
  logger_->Info("Points:\n%s", mila::to_string(config.points).c_str());
  logger_->Info("Bandwidth: %f", config.bandwidth);
  logger_->Info("Number of iterations: %d", config.number_of_iterations);
}
void mila::SequentialMeanShiftApp::PrintResults(const SequentialMeanShiftProfilingResults &results) const {
  logger_->Debug("Throughput: %f points/s", results.points_per_second);
  logger_->Debug("Mean shift duration: %llu us", results.mean_shift_duration);
}
void mila::SequentialMeanShiftApp::PrintResultsStatistics(const mila::SequentialMeanShiftApp::Results &results) const {
  mila::PrintResultStatistics("Throughput", "points/s", results.points_per_second, *logger_);
  mila::PrintResultStatistics("Mean shift duration", "us", results.mean_shift_duration, *logger_);
}
