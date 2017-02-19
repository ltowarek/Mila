#ifndef MILA_BBP_UTILS_H
#define MILA_BBP_UTILS_H

#include <algorithm>
#include <cmath>
#include <chrono>
#include <numeric>
#include <string>
#include <vector>

namespace mila {
std::string ConvertFractionToHex(float number, size_t number_of_digits);
std::vector<std::string> ConvertFractionsToHex(const std::vector<float>& numbers, size_t number_of_digits);
}  // mila
#endif  // MILA_BBP_UTILS_H
