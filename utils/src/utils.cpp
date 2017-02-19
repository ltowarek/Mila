#include "utils.hpp"

float mila::utils::GetValuePerSecond(size_t value, std::chrono::duration<float> duration) {
  auto value_per_second = (duration.count() > 0.0f) ? static_cast<float>(value) / duration.count() : 0.0f;
  return value_per_second;
}

std::string mila::utils::ReadFile(const std::string &file) {
  std::ifstream in(file);
  auto content = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
  return content;
}

std::vector<float> mila::utils::ExtractTimeCountFromVector(const std::vector<std::chrono::microseconds> &input) {
  auto output = std::vector<float>();
  std::transform(input.begin(),
                 input.end(),
                 std::back_inserter(output),
                 [](const std::chrono::microseconds &time) { return time.count(); });
  return output;
}
