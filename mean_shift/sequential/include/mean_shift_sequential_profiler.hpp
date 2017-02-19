#ifndef MILA_MEAN_SHIFT_SEQUENTIAL_PROFILER_HPP
#define MILA_MEAN_SHIFT_SEQUENTIAL_PROFILER_HPP

#include "mean_shift_sequential.hpp"
#include "profiler.hpp"
#include "utils.hpp"

namespace mila {
struct SequentialMeanShiftProfilingResults {
  std::chrono::microseconds mean_shift_duration;
  float points_per_second;
};
class SequentialMeanShiftProfiler : public MeanShift {
 public:
  SequentialMeanShiftProfiler(std::unique_ptr<mila::SequentialMeanShift> mean_shift,
                              std::unique_ptr<mila::Profiler> profiler,
                              const std::shared_ptr<mila::Logger> logger);
  virtual ~SequentialMeanShiftProfiler();

  std::vector<Point> Run(const std::vector<Point> &points, const float bandwidth) override;

  SequentialMeanShiftProfilingResults GetResults() const;
 private:
  const std::unique_ptr<mila::SequentialMeanShift> mean_shift_;
  const std::unique_ptr<mila::Profiler> profiler_;
  const std::shared_ptr<mila::Logger> logger_;
  SequentialMeanShiftProfilingResults results_;

  void SetResultsAfterComputeDigits(const size_t number_of_digits);
  void InitResults();
};
}  // mila
#endif  // MILA_MEAN_SHIFT_SEQUENTIAL_PROFILER_HPP
