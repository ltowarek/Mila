#ifndef MILA_N_BODY_INTERACTIVE_VIEW_APP_H_
#define MILA_N_BODY_INTERACTIVE_VIEW_APP_H_

#include "plugin.h"
#include "n_body_sequential.h"
#include "n_body_parallel.h"
#include "n_body_interactive_view_profiler.h"
#include "statistics.h"

namespace mila {
class ParallelNBodyInteractiveViewApp : public Plugin {
 public:
  ParallelNBodyInteractiveViewApp(const std::shared_ptr<mila::Logger> logger);
  virtual ~ParallelNBodyInteractiveViewApp();
  virtual void Run(int argc, char **argv) const override;
 private:
  struct Parameters {
    std::string action;
    size_t number_of_particles;
    std::string mouse_positions_file;
    std::string particles_file;
    size_t platform_id;
    size_t device_id;
    size_t number_of_iterations;
  };

  struct Results {
    std::vector<float> replay_duration;
    std::vector<float> frames_per_second;
  };

  Parameters ParseCommandLine(int argc, char **argv) const;
  std::vector<mila::NBodyInteractiveViewProfilingResults> RunIterations(const Parameters config) const;
  Results PrepareResults(const std::vector<mila::NBodyInteractiveViewProfilingResults> &raw_results) const;
  void PrintParameters(const Parameters &config) const;
  void PrintResults(const NBodyInteractiveViewProfilingResults &results) const;
  void PrintResultsStatistics(const Results &results) const;

  const std::shared_ptr<mila::Logger> logger_;
};

class SequentialNBodyInteractiveViewApp : public Plugin {
 public:
  SequentialNBodyInteractiveViewApp(const std::shared_ptr<mila::Logger> logger);
  virtual ~SequentialNBodyInteractiveViewApp();
  virtual void Run(int argc, char **argv) const override;
 private:
  struct Parameters {
    std::string action;
    size_t number_of_particles;
    std::string mouse_positions_file;
    std::string particles_file;
    size_t number_of_iterations;
  };

  struct Results {
    std::vector<float> replay_duration;
    std::vector<float> frames_per_second;
  };

  Parameters ParseCommandLine(int argc, char **argv) const;
  std::vector<mila::NBodyInteractiveViewProfilingResults> RunIterations(const Parameters config) const;
  Results PrepareResults(const std::vector<mila::NBodyInteractiveViewProfilingResults> &raw_results) const;
  void PrintParameters(const Parameters &config) const;
  void PrintResults(const NBodyInteractiveViewProfilingResults &results) const;
  void PrintResultsStatistics(const Results &results) const;

  const std::shared_ptr<mila::Logger> logger_;
};
}  // mila
#endif  //MILA_N_BODY_INTERACTIVE_VIEW_APP_H_
