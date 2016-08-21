#include <memory>

#include "bbp_parallel_profiler.h"
#include "version.h"

int main(int argc, char **argv) {
  auto logger = std::shared_ptr<mila::Logger>(mila::LoggerFactory().MakePrintf());
  logger->Info("Version: %s", mila::version::GetVersion().c_str());
  auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, logger);
  logger->Info("Platform name: %s", ocl_app->GetPlatformName().c_str());
  logger->Info("Device name: %s", ocl_app->GetDeviceName().c_str());
  auto bbp = std::unique_ptr<mila::ParallelBBP>(new mila::ParallelBBP(std::move(ocl_app), logger));
  auto profiler = mila::ProfilerFactory().MakeChrono(logger);
  auto bbp_profiler = std::unique_ptr<mila::ParallelBBPProfiler>(new mila::ParallelBBPProfiler(std::move(bbp), std::move(profiler), logger));
  bbp_profiler->Initialize();
  auto number_of_digits = size_t{100};
  auto starting_position = cl_uint{500};
  auto digits = bbp_profiler->ComputeDigits(number_of_digits, starting_position);
  logger->Info("Number of digits: %d", number_of_digits);
  logger->Info("Starting position: %d", starting_position);
  logger->Info("Digits: %s", bbp_profiler->GetDigits(digits).c_str());
  logger->Info("Bandwidth: %f GB/s", bbp_profiler->GetResults().bandwidth);
  logger->Info("Throughput: %f digits/s", bbp_profiler->GetResults().digits_per_second);
  logger->Info("Initialize duration: %llu ms", bbp_profiler->GetResults().initialize_duration);
  logger->Info("Compute digits duration: %llu ms", bbp_profiler->GetResults().compute_digits_duration);
  logger->Info("Enqueue ND range duration: %llu ms", bbp_profiler->GetResults().enqueue_nd_range_duration);
  logger->Info("Read buffer duration: %llu ms", bbp_profiler->GetResults().read_buffer_duration);
  return 0;
}
