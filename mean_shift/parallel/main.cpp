#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "utils.h"
#include "version.h"
#include "mean_shift_parallel_profiler.h"

struct parameters {
  std::string input_file;
  std::string output_file;
  float bandwidth;
  size_t platform_id;
  size_t device_id;
  size_t number_of_iterations;
};

parameters ParseCommandLine(int argc, char **argv) {
  auto config = parameters{};
  // TODO: Verify input and add help message
  config.input_file = std::string(argv[1]);
  config.output_file = std::string(argv[2]);
  config.bandwidth = static_cast<float>(atof(argv[3]));
  config.platform_id = static_cast<size_t>(atoi(argv[4]));
  config.device_id = static_cast<size_t>(atoi(argv[5]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[6]));
  return config;
}

int main(int argc, char **argv) {
  auto config = ParseCommandLine(argc, argv);
  printf("%s\n", mila::version::GetVersion().c_str());

  auto mean_shift_initial =
      mila::meanshift::parallel::MeanShiftImageProcessingProfiler(config.platform_id, config.device_id);
  mean_shift_initial.Run(config.input_file, config.output_file, config.bandwidth);
  auto result = mean_shift_initial.results().at(mean_shift_initial.main_result());
  auto duration = mean_shift_initial.results().at(mean_shift_initial.main_duration());
  printf("Initial results\n");
  printf("%s: %f\n", mean_shift_initial.main_result().c_str(), result);
  printf("Duration [us]: %f\n", duration);
  printf("Platform: %s\n", mean_shift_initial.platform().getName().c_str());
  printf("Device: %s\n", mean_shift_initial.device().getName().c_str());
  printf("Input file: %s\n", config.input_file.c_str());
  printf("Output file: %s\n", config.output_file.c_str());
  printf("Bandwidth: %f\n", config.bandwidth);

  auto results = std::vector<float>(config.number_of_iterations);
  printf("Iterations\n");
  for (size_t i = 0; i < config.number_of_iterations; ++i) {
    auto mean_shift = mila::meanshift::parallel::MeanShiftImageProcessingProfiler(config.platform_id, config.device_id);
    mean_shift.Run(config.input_file, config.output_file, config.bandwidth);
    result = mean_shift.results().at(mean_shift.main_result());
    duration = mean_shift.results().at(mean_shift.main_duration());
    printf("Iteration: %lu\n", i);
    printf("Host statistics:\n");
    printf("Duration: %f us, %s: %f, Bandwidth: %f GB/s\n", duration, mean_shift.main_result().c_str(), result, mean_shift.GetBandwidth());
    printf("OpenCL statistics:\n");
    printf("%s\n", mean_shift.GetOpenCLStatisticsAsString().c_str());
    results[i] = duration;
  }

  printf("Statistics\n");
  printf("Mean: %f\n", mila::utils::Mean(results));
  printf("Median: %f\n", mila::utils::Median(results));
  printf("Variance: %f\n", mila::utils::Variance(results));
  printf("Standard Deviation: %f\n", mila::utils::StandardDeviation(results));
  printf("Coefficient of Variation: %f\n", mila::utils::CoefficientOfVariation(results));

  return 0;
}
