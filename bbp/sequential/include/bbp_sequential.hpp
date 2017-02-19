#ifndef MILA_BBP_SEQUENTIAL_HPP
#define MILA_BBP_SEQUENTIAL_HPP

#include <cmath>
#include <cstddef>
#include <vector>
#include <string>
#include <memory>

#include "bbp.hpp"
#include "bbp_utils.hpp"
#include "logger.hpp"

namespace mila {
class SequentialBBP : public GenericBBP {
 public:
  SequentialBBP(const std::shared_ptr<mila::Logger> logger);
  virtual ~SequentialBBP();

  float ComputeDigit(const size_t position) const;
  float Series(const size_t j, const size_t d) const;  // Compute sum_k 16^(d-k)/(8*k*j)
  float ModularExponentiation(const float b, const float m, size_t e) const;  // Compute b^e mod m
  size_t LargestPowerOfTwoLessOrEqual(const size_t n) const;
  std::vector<float> ComputeDigits(const size_t number_of_digits, const size_t starting_position) override;
 private:
  const std::vector<size_t> powers_of_two = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048,
                                             4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
                                             1048576, 2097152, 4194304, 8388608, 16777216, 33554432};
  const std::shared_ptr<mila::Logger> logger_;
};
}  // mila
#endif  // MILA_BBP_SEQUENTIAL_HPP
