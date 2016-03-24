#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <bbp_sequential_profiler.h>

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
  auto bbp_initial = mila::bbp::sequential::BBPProfiler();
  std::string output = bbp_initial.Run(config.number_of_digits, config.starting_position);
  auto duration = bbp_initial.results().at(bbp_initial.main_result());
  printf("Initial results\n");
  printf("Duration [us]: %lld\n", duration);
  printf("Number of Digits: %d\n", config.number_of_digits);
  printf("Starting Position: %d\n", config.starting_position);
  printf("PI in hex: %s\n", output.c_str());

  auto results = std::vector<float>(config.number_of_iterations);
  printf("Iterations\n");
  for (size_t i = 0; i < config.number_of_iterations; ++i) {
    auto bbp = mila::bbp::sequential::BBPProfiler();
    bbp.Run(config.number_of_digits, config.starting_position);
    duration = bbp.results().at(bbp.main_result());
    printf("Iteration: %d, Duration [us]: %lld\n", i, duration);
    results[i] = duration;
  }

  printf("Statistics\n");
  printf("Mean: %f\n", mila::bbp::utils::Mean(results));
  printf("Median: %f\n", mila::bbp::utils::Median(results));
  printf("Variance: %f\n", mila::bbp::utils::Variance(results));
  printf("Standard Deviation: %f\n", mila::bbp::utils::StandardDeviation(results));
  printf("Coefficient of Variation: %f\n", mila::bbp::utils::CoefficientOfVariation(results));

  return 0;
}
