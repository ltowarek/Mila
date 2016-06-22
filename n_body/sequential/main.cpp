#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "utils.h"
#include "n_body_sequential_profiler.h"

struct parameters {
  std::string input_file;
  int number_of_particles;
  size_t number_of_iterations;
};

parameters ParseCommandLine(int argc, char **argv) {
  auto config = parameters{};
  // TODO: Verify input and add help message
  config.input_file = std::string(argv[1]);
  config.number_of_particles = atoi(argv[2]);
  config.number_of_iterations = static_cast<size_t>(atoi(argv[3]));
  return config;
}

int main(int argc, char **argv) {
  auto config = ParseCommandLine(argc, argv);
  auto n_body_initial = mila::nbody::sequential::NBodySequentialWithInputFileProfiler(config.number_of_particles);
  n_body_initial.Run(config.input_file);
  auto duration = n_body_initial.results().at(n_body_initial.main_result());
  printf("Initial results\n");
  printf("Duration [us]: %lld\n", duration);
  printf("Input file: %s\n", config.input_file.c_str());
  printf("Number of particles: %d\n", config.number_of_particles);

  auto results = std::vector<float>(config.number_of_iterations);
  printf("Iterations\n");
  for (size_t i = 0; i < config.number_of_iterations; ++i) {
    auto n_body = mila::nbody::sequential::NBodySequentialWithInputFileProfiler(config.number_of_particles);
    n_body.Run(config.input_file);
    duration = n_body.results().at(n_body.main_result());
    printf("Iteration: %d, Duration [us]: %lld\n", i, duration);
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
