#ifndef MILA_MEAN_SHIFT_PARALLEL_APP_HPP
#define MILA_MEAN_SHIFT_PARALLEL_APP_HPP

#include "plugin.hpp"
#include "mean_shift_parallel_profiler.hpp"
#include "statistics.hpp"

namespace mila {
class ParallelMeanShiftApp : public Plugin {
 public:
  ParallelMeanShiftApp(const std::shared_ptr<mila::Logger> logger);
  virtual ~ParallelMeanShiftApp();
  virtual void Run(int argc, char **argv) const override;
 private:
  struct Parameters {
    std::vector<Point> points;
    float bandwidth;
    size_t platform_id;
    size_t device_id;
    size_t number_of_iterations;
  };

  struct Results {
    std::vector<float> mean_shift_duration;
    std::vector<float> initialize_duration;
    std::vector<float> read_buffer_with_output_duration;
    std::vector<float> read_buffer_with_distances_durations;
    std::vector<float> copy_buffer_durations;
    std::vector<float> enqueue_nd_range_durations;
    std::vector<float> read_buffer_with_distances_duration;
    std::vector<float> copy_buffer_duration;
    std::vector<float> enqueue_nd_range_duration;
    std::vector<float> points_per_second;
    std::vector<float> bandwidth;
  };

  Parameters ParseCommandLine(int argc, char **argv) const;
  std::vector<mila::ParallelMeanShiftProfilingResults> RunIterations(const Parameters config) const;
  Results PrepareResults(const std::vector<mila::ParallelMeanShiftProfilingResults> &raw_results) const;
  void PrintParameters(const Parameters &config) const;
  void PrintResults(const ParallelMeanShiftProfilingResults &results) const;
  void PrintResultsStatistics(const Results &results) const;

  const std::shared_ptr<mila::Logger> logger_;
};
}  // mila
#endif  //MILA_MEAN_SHIFT_PARALLEL_APP_HPP
