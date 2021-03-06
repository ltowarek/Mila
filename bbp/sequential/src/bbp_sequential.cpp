#include "bbp_sequential.hpp"

mila::SequentialBBP::SequentialBBP(const std::shared_ptr<mila::Logger> logger) : logger_(logger) {

}
mila::SequentialBBP::~SequentialBBP() {

}
float mila::SequentialBBP::ComputeDigit(const size_t position) const {
  const auto series_1 = Series(1, position);
  const auto series_2 = Series(4, position);
  const auto series_3 = Series(5, position);
  const auto series_4 = Series(6, position);
  auto result = 4.0f * series_1 - 2.0f * series_2 - series_3 - series_4;  // BBP formula
  result = result - truncf(result) + 1.0f;
  return result;
}
float mila::SequentialBBP::Series(const size_t j, const size_t d) const {
  auto sum = 0.0f;
  const auto precision = 1e-5;

  for (size_t k = 0; k < d; ++k) {
    const auto ak = 8.0f * k + j;
    const auto p = d - k;
    const auto t = ModularExponentiation(16.0f, ak, p);
    sum += t / ak;
    sum -= truncf(sum);
  }

  for (size_t k = d; k <= d + 100; ++k) {
    const auto ak = 8.0f * k + j;
    const auto p = static_cast<float>(d) - static_cast<float>(k);
    const auto t = powf(16.0f, p) / ak;

    if (t < precision) {
      break;
    }

    sum += t;
    sum -= truncf(sum);
  }

  return sum;
}
float mila::SequentialBBP::ModularExponentiation(const float b, const float m, size_t e) const {
  if (m == 1.0f) {
    return 0.0f;
  }

  auto c = 1.0f;
  const auto p = LargestPowerOfTwoLessOrEqual(e);
  auto t = powf(2.0f, static_cast<float>(p - 1));

  for (size_t i = 0; i < p; ++i) {
    if (e >= t) {
      c *= b;
      c -= trunc(c / m) * m;
      e -= t;
    }

    t *= 0.5f;

    if (t >= 1.0f) {
      c *= c;
      c -= trunc(c / m) * m;
    }
  }

  return c;
}
size_t mila::SequentialBBP::LargestPowerOfTwoLessOrEqual(const size_t n) const {
  auto i = size_t{0};
  for (i = 0; i < powers_of_two.size(); ++i) {
    if (powers_of_two[i] > n) {
      break;
    }
  }
  return i;
}
std::vector<float> mila::SequentialBBP::ComputeDigits(const size_t number_of_digits, const size_t starting_position) {
  auto digits = std::vector<float>(number_of_digits, 0.0f);
  for (size_t i = 0; i < digits.size(); ++i) {
    digits[i] = ComputeDigit(starting_position + i);
  }
  return digits;
}
