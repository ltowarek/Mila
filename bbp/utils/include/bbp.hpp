#ifndef MILA_UTILS_BBP_H
#define MILA_UTILS_BBP_H

#include <vector>
#include <string>

#include "bbp_utils.hpp"

namespace mila {
class BBP {
 public:
  virtual ~BBP() = 0;
  virtual std::vector<float> ComputeDigits(const size_t number_of_digits, const size_t starting_position) = 0;
  virtual std::string GetDigits(const std::vector<float> &digits) const = 0;
};

class GenericBBP : public BBP {
 public:
  virtual ~GenericBBP();
  virtual std::string GetDigits(const std::vector<float> &digits) const override;
};

class BBPProfiler: public BBP {
 public:
  virtual ~BBPProfiler() = 0;
};
}  // mila
#endif  // MILA_UTILS_BBP_H
