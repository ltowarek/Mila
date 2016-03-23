#include <cstdio>
#include <cstdlib>
#include <string>
#include "bbp_parallel_profiler.h"

struct parameters {
  size_t number_of_digits;
  size_t starting_position;
  size_t platform_id;
  size_t device_id;
};

parameters ParseCommandLine(int argc, char **argv) {
  auto config = parameters{0};
  // TODO: Verify input and add help message
  config.number_of_digits = static_cast<size_t>(atoi(argv[1]));
  config.starting_position = static_cast<size_t>(atoi(argv[2]));
  config.platform_id = static_cast<size_t>(atoi(argv[3]));
  config.device_id = static_cast<size_t>(atoi(argv[4]));
  return config;
}

int main(int argc, char **argv) {
  auto config = ParseCommandLine(argc, argv);
  auto bbp = mila::bbp::parallel::BBPProfiler(config.platform_id, config.device_id);
  std::string output = bbp.Run(config.number_of_digits, config.starting_position);
  auto duration = bbp.results().at(bbp.main_result());
  printf("Duration [us]: %lld\n", duration);
  printf("Platform: %s\n", bbp.platform().getName().c_str());
  printf("Device: %s\n", bbp.device().getName().c_str());
  printf("Number of Digits: %d\n", config.number_of_digits);
  printf("Starting Position: %d\n", config.starting_position);
  printf("PI in hex: %s\n", output.c_str());
  return 0;
}

