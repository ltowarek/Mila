#include "bbp_utils.h"

std::string mila::bbp::utils::ConvertFractionToHex(float number, size_t number_of_digits) {
  const auto kHex = std::string("0123456789ABCDEF");
  auto digit = std::string(number_of_digits, '-');
  auto value = fabsf(number);
  for (size_t i = 0; i < number_of_digits; ++i) {
    value = 16.0f * (value - floorf(value));
    digit[i] = kHex[static_cast<size_t>(value)];
  }
  return digit;
}

std::vector<std::string> mila::bbp::utils::ConvertFractionsToHex(const std::vector<float>& numbers,
                                                                 size_t number_of_digits) {
  auto digits = std::vector<std::string>(numbers.size(), "-");
  for (size_t i = 0; i < digits.size(); ++i) {
    digits[i] = ConvertFractionToHex(numbers[i], number_of_digits);
  }
  return digits;
}

float mila::bbp::utils::Mean(const std::vector<float> &values) {
  float sum = std::accumulate(values.begin(), values.end(), 0.0f);
  float mean = sum / values.size();
  return mean;
}

float ::mila::bbp::utils::Variance(const std::vector<float> &values) {
  float mean = mila::bbp::utils::Mean(values);
  std::vector<float> differences(values.size());
  std::transform(values.begin(), values.end(), differences.begin(), [mean](float x) {return x - mean;});
  float square_sum = std::inner_product(differences.begin(), differences.end(), differences.begin(), 0.0f);
  float variance = square_sum / (values.size() - 1);
  return variance;
}

float mila::bbp::utils::StandardDeviation(const std::vector<float> &values) {
  float variance = mila::bbp::utils::Variance(values);
  float standard_deviation = std::sqrt(variance);
  return standard_deviation;
}
