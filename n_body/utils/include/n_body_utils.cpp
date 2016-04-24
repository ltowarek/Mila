#include "n_body_utils.h"

int ::mila::nbody::utils::GenerateRandomValue(int min, int max) {
  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<> distribution(min, max);
  return distribution(generator);
}
