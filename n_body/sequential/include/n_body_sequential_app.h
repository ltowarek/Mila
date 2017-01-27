#ifndef MILA_N_BODY_SEQUENTIAL_APP_H_
#define MILA_N_BODY_SEQUENTIAL_APP_H_

#include "n_body_sequential_profiler.h"
#include "statistics.h"

namespace mila {
class SequentialNBodyApp : public NBodyApp {
 public:
  SequentialNBodyApp(const std::shared_ptr<mila::Logger> logger);
  virtual ~SequentialNBodyApp();
  virtual void Run(int argc, char **argv) const override;
 private:
  struct Parameters {
    size_t number_of_particles;
    size_t number_of_iterations;
  };

  struct Results {
    std::vector<float> particles_per_second;
    std::vector<float> update_particles_duration;
  };

  Parameters ParseCommandLine(int argc, char **argv) const;
  std::vector<mila::SequentialNBodyProfilingResults> RunIterations(const Parameters config) const;
  Results PrepareResults(const std::vector<mila::SequentialNBodyProfilingResults> &raw_results) const;
  void PrintParameters(const Parameters &config) const;
  void PrintResults(const SequentialNBodyProfilingResults &results) const;
  void PrintResultsStatistics(const Results &results) const;

  const std::shared_ptr<mila::Logger> logger_;
};
}  // mila
#endif  //MILA_N_BODY_SEQUENTIAL_APP_H_
