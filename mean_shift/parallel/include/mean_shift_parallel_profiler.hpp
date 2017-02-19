#ifndef MILA_MEAN_SHIFT_PARALLEL_PROFILER_HPP
#define MILA_MEAN_SHIFT_PARALLEL_PROFILER_HPP

#include "mean_shift_parallel.hpp"
#include "statistics.hpp"
#include "utils.hpp"
#include "profiler.hpp"

namespace mila {
struct ParallelMeanShiftProfilingResults {
  std::chrono::microseconds mean_shift_duration;
  std::chrono::microseconds initialize_duration;
  std::chrono::microseconds read_buffer_with_output_duration;
  std::vector<std::chrono::microseconds> read_buffer_with_distances_durations;
  std::vector<std::chrono::microseconds> copy_buffer_durations;
  std::vector<std::chrono::microseconds> enqueue_nd_range_durations;
  float points_per_second;
  float bandwidth;
};

class ParallelMeanShiftProfiler : public MeanShiftProfiler {
 public:
  ParallelMeanShiftProfiler(std::unique_ptr<ParallelMeanShift> mean_shift,
                            std::unique_ptr<Profiler> profiler,
                            const std::shared_ptr<Logger> logger);
  virtual ~ParallelMeanShiftProfiler() override;

  void Initialize();
  std::vector<Point> Run(const std::vector<Point> &points, const float bandwidth) override;
  virtual ParallelMeanShiftProfilingResults GetResults() const;
 private:
  const std::unique_ptr<mila::ParallelMeanShift> mean_shift_;
  const std::unique_ptr<Profiler> profiler_;
  const std::shared_ptr<Logger> logger_;
  ParallelMeanShiftProfilingResults results_;

  void InitResults();
  float ComputeBandwidthAsGBPS(const size_t number_of_work_items, const float seconds);
  void SetResultsAfterRun(const size_t number_of_points);
  void SetResultsAfterInitialize();
};
}  // mila
#endif  // MILA_MEAN_SHIFT_PARALLEL_PROFILER_HPP
