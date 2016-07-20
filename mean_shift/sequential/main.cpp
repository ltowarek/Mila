#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "utils.h"
#include "version.h"
#include "mean_shift_sequential_profiler.h"

struct parameters {
  std::string input_file;
  std::string output_file;
  float bandwidth;
  size_t number_of_iterations;
};

parameters ParseCommandLine(int argc, char **argv) {
  auto config = parameters{};
  // TODO: Verify input and add help message
  config.input_file = std::string(argv[1]);
  config.output_file = std::string(argv[2]);
  config.bandwidth = static_cast<float>(atof(argv[3]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[4]));
  return config;
}

int main(int argc, char **argv) {
  auto config = ParseCommandLine(argc, argv);
  printf("%s\n", mila::version::PrintVersion().c_str());

  auto mean_shift_initial = mila::meanshift::sequential::MeanShiftImageProcessingProfiler();
  mean_shift_initial.Run(config.input_file, config.output_file, config.bandwidth);
  auto result = mean_shift_initial.results().at(mean_shift_initial.main_result());
  auto duration = mean_shift_initial.results().at(mean_shift_initial.main_duration());
  printf("Initial results\n");
  printf("%s: %f\n", mean_shift_initial.main_result().c_str(), result);
  printf("Duration [us]: %f\n", duration);
  printf("Input file: %s\n", config.input_file.c_str());
  printf("Output file: %s\n", config.output_file.c_str());
  printf("Bandwidth: %f\n", config.bandwidth);

  auto results = std::vector<float>(config.number_of_iterations);
  printf("Iterations\n");
  for (size_t i = 0; i < config.number_of_iterations; ++i) {
    auto mean_shift = mila::meanshift::sequential::MeanShiftImageProcessingProfiler();
    mean_shift.Run(config.input_file, config.output_file, config.bandwidth);
    result = mean_shift.results().at(mean_shift.main_result());
    duration = mean_shift.results().at(mean_shift.main_duration());
    printf("Iteration: %lu, %s: %f, Duration [us]: %f\n", i, mean_shift.main_result().c_str(), result, duration);
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

