#include <cstdio>
#include <cstdlib>
#include <string>
#include "bbp_sequential.h"

struct parameters {
  size_t number_of_digits;
  size_t starting_position;
};

parameters ParseCommandLine(int argc, char** argv) {
  auto config = parameters{0};
  // TODO: Verify input and add help message
  config.number_of_digits = static_cast<size_t>(atoi(argv[1]));
  config.starting_position = static_cast<size_t>(atoi(argv[2]));
  return config;
}

int main(int argc, char** argv) {
  auto config = ParseCommandLine(argc, argv);
  auto bbp = mila::bbp::sequential::BBP();
  std::string output = bbp.Run(config.number_of_digits, config.starting_position);
  printf("Number of Digits: %d\n", config.number_of_digits);
  printf("Starting Position: %d\n", config.starting_position);
  printf("PI in hex: %s\n", output.c_str());
  return 0;
}
