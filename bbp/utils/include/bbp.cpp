#include "bbp.h"

mila::BBP::~BBP() {

}

std::string mila::GenericBBP::GetDigits(const std::vector<float> &digits) const {
  const auto hex_digits = mila::bbp::utils::ConvertFractionsToHex(digits, 1);
  auto output = std::string("");
  for (const auto digit : hex_digits) {
    output += digit[0];
  }
  return output;
}

mila::GenericBBP::~GenericBBP() {

}

mila::BBPProfiler::~BBPProfiler() {

}
