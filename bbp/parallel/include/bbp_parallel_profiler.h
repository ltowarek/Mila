#ifndef MILA_BBP_PARALLEL_PROFILER_H_
#define MILA_BBP_PARALLEL_PROFILER_H_

#include <chrono>
#include <map>
#include "bbp_parallel.h"

namespace mila {
namespace bbp {
namespace parallel {
class BBPProfiler : public BBP {
 public:
  BBPProfiler();
  BBPProfiler(float precision);
  BBPProfiler(size_t platform_id, size_t device_id);

  void Initialize() override;
  std::string Run(size_t number_of_digits, size_t starting_position) override;

  std::string main_result() const;
  std::map<std::string, int64_t> results() const;
 private:
  const std::string main_result_;
  std::map<std::string, int64_t> results_;
};
};  // parallel
};  // bbp
}  // mila

#endif  // MILA_BBP_PARALLEL_PROFILER_H_
