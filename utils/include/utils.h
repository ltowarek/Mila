#ifndef MILA_UTILS_H_
#define MILA_UTILS_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <chrono>

namespace mila {
namespace utils {

std::string ReadFile(const std::string &file);
float GetValuePerSecond(size_t value, std::chrono::duration<float> duration);

template<typename T>
T Median(const std::vector<T> &values) {
  auto tmp_values = values;
  std::sort(tmp_values.begin(), tmp_values.end());
  auto median = 0.0f;
  if (values.size() % 2 == 0) {
    median = (tmp_values[tmp_values.size() / 2.0f - 1.0f] + tmp_values[tmp_values.size() / 2.0f]) / 2.0f;
  } else {
    median = tmp_values[tmp_values.size() / 2];
  }
  return static_cast<T>(median);
}

template<typename T>
T Mean(const std::vector<T> &values) {
  auto sum = std::accumulate(values.begin(), values.end(), 0.0f);
  auto mean = sum / values.size();
  return static_cast<T>(mean);
}

template<typename T>
T Variance(const std::vector<T> &values) {
  auto mean = Mean(values);
  auto differences = std::vector<T>(values.size());
  std::transform(values.begin(), values.end(), differences.begin(), [mean](T x) {return x - mean;});
  auto square_sum = std::inner_product(differences.begin(), differences.end(), differences.begin(), 0.0f);
  auto variance = square_sum / (values.size() - 1);
  return static_cast<T>(variance);
}

template<typename T>
T StandardDeviation(const std::vector<T> &values) {
  auto variance = Variance(values);
  auto standard_deviation = std::sqrt(variance);
  return static_cast<T>(standard_deviation);
}

template<typename T>
T CoefficientOfVariation(const std::vector<T> &values) {
  auto mean = Mean(values);
  auto standard_deviation = StandardDeviation(values);
  auto coefficient_of_variation = (standard_deviation / mean);
  return static_cast<T>(coefficient_of_variation);
}

};  // utils
}  // mila

#endif  // MILA_UTILS_H_
