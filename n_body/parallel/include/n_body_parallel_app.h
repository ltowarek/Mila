#ifndef MILA_N_BODY_PARALLEL_APP_H_
#define MILA_N_BODY_PARALLEL_APP_H_

#include "plugin.h"
#include "n_body_parallel_profiler.h"
#include "statistics.h"

namespace mila {
class ParallelNBodyApp : public Plugin {
 public:
  ParallelNBodyApp(const std::shared_ptr<mila::Logger> logger);
  virtual ~ParallelNBodyApp();
  virtual void Run(int argc, char **argv) const override;
 private:
  struct Parameters {
    size_t number_of_particles;
    size_t platform_id;
    size_t device_id;
    size_t number_of_iterations;
  };

  struct Results {
    std::vector<float> particles_per_second;
    std::vector<float> update_particles_duration;
    std::vector<float> initialize_duration;
    std::vector<float> enqueue_nd_range_duration;
    std::vector<float> read_buffer_duration;
    std::vector<float> bandwidth;
  };

  Parameters ParseCommandLine(int argc, char **argv) const;
  std::vector<mila::ParallelNBodyProfilingResults> RunIterations(const Parameters config) const;
  Results PrepareResults(const std::vector<mila::ParallelNBodyProfilingResults> &raw_results) const;
  void PrintParameters(const Parameters &config) const;
  void PrintResults(const ParallelNBodyProfilingResults &results) const;
  void PrintResultsStatistics(const Results &results) const;

  const std::shared_ptr<mila::Logger> logger_;
};
}  // mila
#endif  //MILA_N_BODY_PARALLEL_APP_H_
