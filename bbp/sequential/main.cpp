#include <cstdio>
#include <string>
#include "bbp_sequential.h"

int main() {
  mila::bbp::sequential::BBP bbp;
  size_t number_of_digits = 10;
  size_t starting_position = 10;
  std::string output = bbp.Run(number_of_digits, starting_position);
  printf("Number of Digits: %d\n", number_of_digits);
  printf("Starting Position: %d\n", starting_position);
  printf("PI in hex: %s\n", output.c_str());
  return 0;
}
