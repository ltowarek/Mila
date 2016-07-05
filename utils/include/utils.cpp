#include "utils.h"

float mila::utils::Mean(const std::vector<float> &values) {
  auto sum = std::accumulate(values.begin(), values.end(), 0.0f);
  auto mean = sum / values.size();
  return mean;
}

float mila::utils::Variance(const std::vector<float> &values) {
  auto mean = mila::utils::Mean(values);
  auto differences = std::vector<float>(values.size());
  std::transform(values.begin(), values.end(), differences.begin(), [mean](float x) {return x - mean;});
  auto square_sum = std::inner_product(differences.begin(), differences.end(), differences.begin(), 0.0f);
  auto variance = square_sum / (values.size() - 1);
  return variance;
}

float mila::utils::StandardDeviation(const std::vector<float> &values) {
  auto variance = mila::utils::Variance(values);
  auto standard_deviation = std::sqrt(variance);
  return standard_deviation;
}

float mila::utils::CoefficientOfVariation(const std::vector<float> &values) {
  auto mean = mila::utils::Mean(values);
  auto standard_deviation = mila::utils::StandardDeviation(values);
  auto coefficient_of_variation = (standard_deviation / mean);
  return coefficient_of_variation;
}

float mila::utils::Median(const std::vector<float> &values) {
  auto tmp_values = values;
  std::sort(tmp_values.begin(), tmp_values.end());
  auto median = 0.0f;
  if (values.size() % 2 == 0) {
    median = (tmp_values[tmp_values.size() / 2.0f - 1.0f] + tmp_values[tmp_values.size() / 2.0f]) / 2.0f;
  } else {
    median = tmp_values[tmp_values.size() / 2];
  }
  return median;
}

std::string mila::utils::ReadFile(const std::string &file) {
  std::ifstream in(file);
  auto content = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
  return content;
}

float mila::utils::GetValuePerSecond(size_t value, std::chrono::duration<float> duration) {
  auto value_per_second = (duration.count() > 0.0f) ? static_cast<float>(value) / duration.count() : 0.0f;
  return value_per_second;
}
