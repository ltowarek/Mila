#ifndef MILA_BBP_PARALLEL_APP_HPP
#define MILA_BBP_PARALLEL_APP_HPP

#include "plugin.hpp"
#include "bbp_parallel_profiler.hpp"
#include "statistics.hpp"

namespace mila {
class ParallelBBPApp : public Plugin {
 public:
  ParallelBBPApp(const std::shared_ptr<mila::Logger> logger);
  virtual ~ParallelBBPApp();
  void Run(int argc, char **argv) const override;
 private:
  struct Parameters {
    size_t number_of_digits;
    cl_uint starting_position;
    size_t platform_id;
    size_t device_id;
    size_t number_of_iterations;
  };

  struct Results {
    std::vector<float> bandwidth;
    std::vector<float> digits_per_second;
    std::vector<float> initialize_duration;
    std::vector<float> compute_digits_duration;
    std::vector<float> enqueue_nd_range_duration;
    std::vector<float> read_buffer_duration;
  };

  Parameters ParseCommandLine(int argc, char **argv) const;
  std::vector<mila::ParallelBBPProfilingResults> RunIterations(const Parameters config) const;
  Results PrepareResults(const std::vector<mila::ParallelBBPProfilingResults> &raw_results) const;
  void PrintParameters(const Parameters &config) const;
  void PrintResults(const ParallelBBPProfilingResults &results) const;
  void PrintResultsStatistics(const Results &results) const;

  const std::shared_ptr<mila::Logger> logger_;
};
}  // mila
#endif //MILA_BBP_PARALLEL_APP_HPP
