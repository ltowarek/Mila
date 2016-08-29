#include "bbp_parallel_app.h"

mila::ParallelBBPApp::ParallelBBPApp(std::shared_ptr<mila::Logger> logger): logger_(logger) {

}
void mila::ParallelBBPApp::Run(int argc, char **argv) const {
  auto config = ParseCommandLine(argc, argv);
  PrintParameters(config);
  auto raw_results = RunIterations(config);
  auto prepared_results = PrepareResults(raw_results);
  PrintResultsStatistics(prepared_results);
}
mila::ParallelBBPApp::Parameters mila::ParallelBBPApp::ParseCommandLine(int argc, char **argv) const {
  if (argc < 6) {
    throw std::runtime_error("Wrong number of parameters: " + std::to_string(argc));
  }
  auto config = Parameters{0};
  config.number_of_digits = static_cast<size_t>(atoi(argv[1]));
  config.starting_position = static_cast<cl_uint>(atoi(argv[2]));
  config.platform_id = static_cast<size_t>(atoi(argv[3]));
  config.device_id = static_cast<size_t>(atoi(argv[4]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[5]));
  return config;
}
std::vector<mila::ParallelBBPProfilingResults> mila::ParallelBBPApp::RunIterations(const Parameters config) const {
  auto results = std::vector<mila::ParallelBBPProfilingResults>();
  const auto warm_up_iterations = 1;
  for (size_t i = 0; i < config.number_of_iterations + warm_up_iterations; ++i) {
    logger_->Debug("Iteration: %d", i);

    auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(config.platform_id, config.device_id, logger_);

    if (i == 0) {
      logger_->Info("Platform name: %s", ocl_app->GetPlatformName().c_str());
      logger_->Info("Device name: %s", ocl_app->GetDeviceName().c_str());
    }

    auto bbp = std::unique_ptr<mila::ParallelBBP>(new mila::ParallelBBP(std::move(ocl_app), logger_));
    auto profiler = mila::ProfilerFactory().MakeChrono(logger_);
    auto bbp_profiler = std::unique_ptr<mila::ParallelBBPProfiler>(new mila::ParallelBBPProfiler(std::move(bbp), std::move(profiler), logger_));
    bbp_profiler->Initialize();
    auto digits = bbp_profiler->ComputeDigits(config.number_of_digits, config.starting_position);
    auto digits_str = bbp_profiler->GetDigits(digits);

    if (i == 0) {
      logger_->Info("Digits: %s", digits_str.c_str());
    } else {
      logger_->Debug("Digits: %s", digits_str.c_str());
    }

    PrintResults(bbp_profiler->GetResults());

    if (i >= warm_up_iterations) {
      results.push_back(bbp_profiler->GetResults());
    }
  }
  return results;
}
mila::ParallelBBPApp::Results mila::ParallelBBPApp::PrepareResults(const std::vector<mila::ParallelBBPProfilingResults> &raw_results) const {
  auto prepared_results = Results{};
  for (const auto& result : raw_results) {
    prepared_results.bandwidth.push_back(result.bandwidth);
    prepared_results.digits_per_second.push_back(result.digits_per_second);
    prepared_results.initialize_duration.push_back(result.initialize_duration.count());
    prepared_results.compute_digits_duration.push_back(result.compute_digits_duration.count());
    prepared_results.enqueue_nd_range_duration.push_back(result.enqueue_nd_range_duration.count());
    prepared_results.read_buffer_duration.push_back(result.read_buffer_duration.count());
  }
  return prepared_results;
}
void mila::ParallelBBPApp::PrintParameters(const Parameters &config) const {
  logger_->Info("Number of digits: %d", config.number_of_digits);
  logger_->Info("Starting position: %d", config.starting_position);
  logger_->Info("Number of iterations: %d", config.number_of_iterations);
  logger_->Info("Platform id: %d", config.platform_id);
  logger_->Info("Device id: %d", config.device_id);
}
void mila::ParallelBBPApp::PrintResultsStatistics(const Results &results) const {
  mila::PrintResultStatistics("Bandwidth", "GB/s", results.bandwidth, *logger_);
  mila::PrintResultStatistics("Throughput", "digits/s", results.digits_per_second, *logger_);
  mila::PrintResultStatistics("Initialize duration", "us", results.initialize_duration, *logger_);
  mila::PrintResultStatistics("Compute digits duration", "us", results.compute_digits_duration, *logger_);
  mila::PrintResultStatistics("Enqueue ND range duration", "us", results.enqueue_nd_range_duration, *logger_);
  mila::PrintResultStatistics("Read buffer duration", "us", results.read_buffer_duration, *logger_);
}
void mila::ParallelBBPApp::PrintResults(const ParallelBBPProfilingResults &results) const {
  logger_->Debug("Bandwidth: %f GB/s", results.bandwidth);
  logger_->Debug("Throughput: %f digits/s", results.digits_per_second);
  logger_->Debug("Initialize duration: %llu us", results.initialize_duration);
  logger_->Debug("Compute digits duration: %llu us", results.compute_digits_duration);
  logger_->Debug("Enqueue ND range duration: %llu us", results.enqueue_nd_range_duration);
  logger_->Debug("Read buffer duration: %llu us", results.read_buffer_duration);
}
mila::ParallelBBPApp::~ParallelBBPApp() {

}
