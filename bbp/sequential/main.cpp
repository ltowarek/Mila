#include <cstdio>
#include <string>
#include "bbp_sequential.h"

struct parameters {
  size_t number_of_digits;
  size_t starting_position;
};

int main() {
  parameters config;
  config.number_of_digits = 10;
  config.starting_position = 10;
  mila::bbp::sequential::BBP bbp;
  std::string output = bbp.Run(config.number_of_digits, config.starting_position);
  printf("Number of Digits: %d\n", config.number_of_digits);
  printf("Starting Position: %d\n", config.starting_position);
  printf("PI in hex: %s\n", output.c_str());
  return 0;
}
