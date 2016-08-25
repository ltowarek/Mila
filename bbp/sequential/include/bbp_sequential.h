#ifndef MILA_BBP_SEQUENTIAL_H_
#define MILA_BBP_SEQUENTIAL_H_

#include <cmath>
#include <cstddef>
#include <vector>
#include <string>
#include <memory>

#include "bbp.h"
#include "bbp_utils.h"
#include "logger.h"

namespace mila {
class SequentialBBP : public GenericBBP {
 public:
  SequentialBBP(const std::shared_ptr<mila::Logger> logger);
  virtual ~SequentialBBP();

  float ComputeDigit(size_t position) const;
  float Series(size_t j, size_t d) const;  // Compute sum_k 16^(d-k)/(8*k*j)
  float ModularExponentiation(float b, size_t e, float m) const;  // Compute b^e mod m
  size_t LargestPowerOfTwoLessOrEqual(size_t n) const;
  std::vector<float> ComputeDigits(const size_t number_of_digits, const size_t starting_position) override;
  virtual std::string Run(size_t number_of_digits, size_t starting_position);
 private:
  const std::vector<size_t> powers_of_two = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048,
                                             4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
                                             1048576, 2097152, 4194304, 8388608, 16777216, 33554432};
  const std::shared_ptr<mila::Logger> logger_;
};
}  // mila

#endif  // MILA_BBP_SEQUENTIAL_H_
