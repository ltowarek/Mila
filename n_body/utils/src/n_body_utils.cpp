#include "../include/n_body_utils.hpp"

float mila::GenerateRandomValue(float min, float max) {
  // Constant seed provides stable results
  static std::mt19937 generator(0);
  static std::uniform_real_distribution<float> distribution(min, max);
  return distribution(generator);
}
