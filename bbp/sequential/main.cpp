#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "utils.h"
#include "version.h"
#include "bbp_sequential_profiler.h"

struct parameters {
  size_t number_of_digits;
  size_t starting_position;
  size_t number_of_iterations;
};

parameters ParseCommandLine(int argc, char **argv) {
  auto config = parameters{0};
  // TODO: Verify input and add help message
  config.number_of_digits = static_cast<size_t>(atoi(argv[1]));
  config.starting_position = static_cast<size_t>(atoi(argv[2]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[3]));
  return config;
}

int main(int argc, char **argv) {
  auto config = ParseCommandLine(argc, argv);
  printf("%s\n", mila::version::PrintVersion().c_str());

  auto bbp_initial = mila::bbp::sequential::BBPProfiler();
  std::string output = bbp_initial.Run(config.number_of_digits, config.starting_position);
  auto result = bbp_initial.results().at(bbp_initial.main_result());
  auto duration = bbp_initial.results().at(bbp_initial.main_duration());
  printf("Initial results\n");
  printf("%s: %f\n", bbp_initial.main_result().c_str(), result);
  printf("Duration [us]: %f\n", duration);
  printf("Number of Digits: %lu\n", config.number_of_digits);
  printf("Starting Position: %lu\n", config.starting_position);
  printf("PI in hex: %s\n", output.c_str());

  auto results = std::vector<float>(config.number_of_iterations);
  printf("Iterations\n");
  for (size_t i = 0; i < config.number_of_iterations; ++i) {
    auto bbp = mila::bbp::sequential::BBPProfiler();
    bbp.Run(config.number_of_digits, config.starting_position);
    result = bbp.results().at(bbp.main_result());
    duration = bbp.results().at(bbp.main_duration());
    printf("Iteration: %lu, %s: %f, Duration [us]: %f\n", i, bbp.main_result().c_str(), result, duration);
    results[i] = result;
  }

  printf("Statistics\n");
  printf("Mean: %f\n", mila::utils::Mean(results));
  printf("Median: %f\n", mila::utils::Median(results));
  printf("Variance: %f\n", mila::utils::Variance(results));
  printf("Standard Deviation: %f\n", mila::utils::StandardDeviation(results));
  printf("Coefficient of Variation: %f\n", mila::utils::CoefficientOfVariation(results));

  return 0;
}
