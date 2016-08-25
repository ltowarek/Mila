#ifndef MILA_UTILS_BBP_H_
#define MILA_UTILS_BBP_H_

#include <vector>
#include <string>

#include "bbp_utils.h"

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

class BBPApp {
 public:
  virtual ~BBPApp() = 0;
  virtual void Run(int argc, char **argv) const = 0;
};
}  // mila

#endif  // MILA_UTILS_BBP_H_