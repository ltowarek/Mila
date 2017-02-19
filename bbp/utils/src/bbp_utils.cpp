#include "../include/bbp_utils.hpp"

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
