#include "utils.h"

float mila::utils::GetValuePerSecond(size_t value, std::chrono::duration<float> duration) {
  auto value_per_second = (duration.count() > 0.0f) ? static_cast<float>(value) / duration.count() : 0.0f;
  return value_per_second;
}

std::string mila::utils::ReadFile(const std::string &file) {
  std::ifstream in(file);
  auto content = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
  return content;
}
