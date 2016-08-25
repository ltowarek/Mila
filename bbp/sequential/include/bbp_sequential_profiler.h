#ifndef MILA_BBP_SEQUENTIAL_PROFILER_H_
#define MILA_BBP_SEQUENTIAL_PROFILER_H_

#include <chrono>
#include <map>
#include "bbp_sequential.h"
#include "utils.h"

namespace mila {
class SequentialBBPProfiler : public SequentialBBP {
 public:
  SequentialBBPProfiler(const std::shared_ptr<Logger> logger);
  virtual ~SequentialBBPProfiler();

  std::string Run(size_t number_of_digits, size_t starting_position) override;

  std::string main_result() const;
  std::string main_duration() const;
  std::map<std::string, float> results() const;
 private:
  const std::string main_result_;
  const std::string main_duration_;
  std::map<std::string, float> results_;
};
}  // mila
#endif  // MILA_BBP_SEQUENTIAL_PROFILER_H_
