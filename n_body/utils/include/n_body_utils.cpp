#include "n_body_utils.h"

float mila::nbody::utils::GenerateRandomValue(float min, float max) {
  static std::random_device device;
  static std::mt19937 generator(device());
  static std::uniform_real_distribution<float> distribution(min, max);
  return distribution(generator);
}
