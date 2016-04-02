#ifndef MILA_BBP_UTILS_H_
#define MILA_BBP_UTILS_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

namespace mila {
namespace bbp {
namespace utils {

std::string ConvertFractionToHex(float number, size_t number_of_digits);
std::vector<std::string> ConvertFractionsToHex(const std::vector<float>& numbers, size_t number_of_digits);
std::string ReadFile(const std::string &file);

};  // utils
};  // bbp
}  // mila

#endif  // MILA_BBP_UTILS_H_
