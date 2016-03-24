#ifndef MILA_BBP_PARALLEL_H_
#define MILA_BBP_PARALLEL_H_

#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "clpp.h"

#include "bbp_utils.h"

namespace mila {
namespace bbp {
namespace parallel {
class BBP {
 public:
  BBP();
  BBP(float precision);
  BBP(size_t platform_id, size_t device_id);
  ~BBP();

  virtual void Initialize();
  virtual std::string Run(size_t number_of_digits, size_t starting_position);
  std::vector<float> ComputeDigits(size_t number_of_digits, size_t starting_position);

  float precision() const;
  size_t platform_id() const;
  size_t device_id() const;
  clpp::Platform platform() const;
  clpp::Device device() const;
  clpp::Context context() const;
  clpp::Queue queue() const;
  clpp::Kernel kernel() const;
 private:

  const float precision_;
  size_t platform_id_;
  size_t device_id_;
  clpp::Platform platform_;
  clpp::Device device_;
  clpp::Context context_;
  clpp::Queue queue_;
  clpp::Kernel kernel_;
};
};  // parallel
};  // bbp
}  // mila

#endif  // MILA_BBP_PARALLEL_H_
