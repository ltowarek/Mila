#ifndef MILA_BBP_SEQUENTIAL_PROFILER_H
#define MILA_BBP_SEQUENTIAL_PROFILER_H

#include "bbp_sequential.hpp"
#include "profiler.hpp"

namespace mila {
struct SequentialBBPProfilingResults {
  std::chrono::microseconds compute_digits_duration;
  float digits_per_second;
};
class SequentialBBPProfiler : public BBPProfiler {
 public:
  SequentialBBPProfiler(std::unique_ptr<mila::SequentialBBP> bbp_,
                        std::unique_ptr<mila::Profiler> profiler,
                        const std::shared_ptr<mila::Logger> logger);
  virtual ~SequentialBBPProfiler();

  virtual std::vector<float> ComputeDigits(const size_t number_of_digits, const size_t starting_position) override;
  virtual std::string GetDigits(const std::vector<float> &digits) const override;
  virtual SequentialBBPProfilingResults GetResults() const;
 private:
  const std::unique_ptr<mila::SequentialBBP> bbp_;
  const std::unique_ptr<mila::Profiler> profiler_;
  const std::shared_ptr<mila::Logger> logger_;
  SequentialBBPProfilingResults results_;

  void SetResultsAfterComputeDigits(const size_t number_of_digits);
  void InitResults();
};
}  // mila
#endif  // MILA_BBP_SEQUENTIAL_PROFILER_H
