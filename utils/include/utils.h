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

float Mean(const std::vector<float>& values);
float Median(const std::vector<float>& values);
float Variance(const std::vector<float>& values);
float StandardDeviation(const std::vector<float>& values);
float CoefficientOfVariation(const std::vector<float>& values);
std::string ReadFile(const std::string &file);
float GetValuePerSecond(size_t value, std::chrono::duration<float> duration);

};  // utils
}  // mila

#endif  // MILA_UTILS_H_
