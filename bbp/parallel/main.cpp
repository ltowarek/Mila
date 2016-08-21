#include <memory>

#include "bbp_parallel_profiler.h"
#include "version.h"

struct parameters {
  size_t number_of_digits;
  cl_uint starting_position;
  size_t platform_id;
  size_t device_id;
  size_t number_of_iterations;
};

parameters ParseCommandLine(int argc, char **argv) {
  auto config = parameters{0};
  config.number_of_digits = static_cast<size_t>(atoi(argv[1]));
  config.starting_position = static_cast<cl_uint>(atoi(argv[2]));
  config.platform_id = static_cast<size_t>(atoi(argv[3]));
  config.device_id = static_cast<size_t>(atoi(argv[4]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[5]));
  return config;
}

int main(int argc, char **argv) {
  auto config = ParseCommandLine(argc, argv);

  auto logger = std::shared_ptr<mila::Logger>(mila::LoggerFactory().MakePrintf());
  logger->Info("Version: %s", mila::version::GetVersion().c_str());
  logger->Info("Number of digits: %d", config.number_of_digits);
  logger->Info("Starting position: %d", config.starting_position);
  logger->Info("Number of iterations: %d", config.number_of_iterations);

  auto results = std::vector<mila::ParallelBBPProfilingResults>(config.number_of_iterations);
  for (size_t i = 0; i < config.number_of_iterations; ++i) {
    logger->Debug("Iteration: %d", i);
    auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(config.platform_id, config.device_id, logger);
    if (i == 0) {
      logger->Info("Platform name: %s", ocl_app->GetPlatformName().c_str());
      logger->Info("Device name: %s", ocl_app->GetDeviceName().c_str());
    }
    auto bbp = std::unique_ptr<mila::ParallelBBP>(new mila::ParallelBBP(std::move(ocl_app), logger));
    auto profiler = mila::ProfilerFactory().MakeChrono(logger);
    auto bbp_profiler = std::unique_ptr<mila::ParallelBBPProfiler>(new mila::ParallelBBPProfiler(std::move(bbp), std::move(profiler), logger));
    bbp_profiler->Initialize();
    auto digits = bbp_profiler->ComputeDigits(config.number_of_digits, config.starting_position);
    logger->Debug("Digits: %s", bbp_profiler->GetDigits(digits).c_str());
    logger->Debug("Bandwidth: %f GB/s", bbp_profiler->GetResults().bandwidth);
    logger->Debug("Throughput: %f digits/s", bbp_profiler->GetResults().digits_per_second);
    logger->Debug("Initialize duration: %llu us", bbp_profiler->GetResults().initialize_duration);
    logger->Debug("Compute digits duration: %llu us", bbp_profiler->GetResults().compute_digits_duration);
    logger->Debug("Enqueue ND range duration: %llu us", bbp_profiler->GetResults().enqueue_nd_range_duration);
    logger->Debug("Read buffer duration: %llu us", bbp_profiler->GetResults().read_buffer_duration);
    results[i] = bbp_profiler->GetResults();
  }

  auto all_bandwidth = std::vector<float>();
  auto all_digits_per_second = std::vector<float>();
  auto all_initialize_duration = std::vector<float>();
  auto all_compute_digits_duration = std::vector<float>();
  auto all_enqueue_nd_range_duration = std::vector<float>();
  auto all_read_buffer_duration = std::vector<float>();

  for (const auto& result : results) {
    all_bandwidth.push_back(result.bandwidth);
    all_digits_per_second.push_back(result.digits_per_second);
    all_initialize_duration.push_back(result.initialize_duration.count());
    all_compute_digits_duration.push_back(result.compute_digits_duration.count());
    all_enqueue_nd_range_duration.push_back(result.enqueue_nd_range_duration.count());
    all_read_buffer_duration.push_back(result.read_buffer_duration.count());
  }

  logger->Info("Bandwidth mean: %f GB/s", mila::utils::Mean(all_bandwidth));
  logger->Info("Bandwidth median: %f GB/s", mila::utils::Median(all_bandwidth));
  logger->Info("Bandwidth standard deviation: %f GB/s", mila::utils::StandardDeviation(all_bandwidth));
  logger->Info("Bandwidth coefficient of variation: %f", mila::utils::CoefficientOfVariation(all_bandwidth));

  logger->Info("Throughput mean: %f digits/s", mila::utils::Mean(all_digits_per_second));
  logger->Info("Throughput median: %f digits/s", mila::utils::Median(all_digits_per_second));
  logger->Info("Throughput standard deviation: %f digits/s", mila::utils::StandardDeviation(all_digits_per_second));
  logger->Info("Throughput coefficient of variation: %f", mila::utils::CoefficientOfVariation(all_digits_per_second));

  logger->Info("Initialize duration mean: %f us", mila::utils::Mean(all_initialize_duration));
  logger->Info("Initialize duration median: %f us", mila::utils::Median(all_initialize_duration));
  logger->Info("Initialize duration standard deviation: %f us", mila::utils::StandardDeviation(all_initialize_duration));
  logger->Info("Initialize duration coefficient of variation: %f", mila::utils::CoefficientOfVariation(all_initialize_duration));

  logger->Info("Compute digits duration mean: %f us", mila::utils::Mean(all_compute_digits_duration));
  logger->Info("Compute digits duration median: %f us", mila::utils::Median(all_compute_digits_duration));
  logger->Info("Compute digits duration standard deviation: %f us", mila::utils::StandardDeviation(all_compute_digits_duration));
  logger->Info("Compute digits duration coefficient of variation: %f", mila::utils::CoefficientOfVariation(all_compute_digits_duration));

  logger->Info("Enqueue ND range duration mean: %f us", mila::utils::Mean(all_enqueue_nd_range_duration));
  logger->Info("Enqueue ND range duration median: %f us", mila::utils::Median(all_enqueue_nd_range_duration));
  logger->Info("Enqueue ND range duration standard deviation: %f us", mila::utils::StandardDeviation(all_enqueue_nd_range_duration));
  logger->Info("Enqueue ND range duration coefficient of variation: %f", mila::utils::CoefficientOfVariation(all_enqueue_nd_range_duration));

  logger->Info("Read buffer duration mean: %f us", mila::utils::Mean(all_read_buffer_duration));
  logger->Info("Read buffer duration median: %f us", mila::utils::Median(all_read_buffer_duration));
  logger->Info("Read buffer duration standard deviation: %f us", mila::utils::StandardDeviation(all_read_buffer_duration));
  logger->Info("Read buffer duration coefficient of variation: %f", mila::utils::CoefficientOfVariation(all_read_buffer_duration));

  return 0;
}
