#ifndef MILA_BBP_SEQUENTIAL_APP_HPP
#define MILA_BBP_SEQUENTIAL_APP_HPP

#include "plugin.hpp"
#include "bbp_sequential_profiler.hpp"
#include "statistics.hpp"

namespace mila {
class SequentialBBPApp : public Plugin {
 public:
  SequentialBBPApp(const std::shared_ptr<mila::Logger> logger);
  virtual ~SequentialBBPApp();
  virtual void Run(int argc, char **argv) const override;
 private:
  struct Parameters {
    size_t number_of_digits;
    size_t starting_position;
    size_t number_of_iterations;
  };

  struct Results {
    std::vector<float> digits_per_second;
    std::vector<float> compute_digits_duration;
  };

  Parameters ParseCommandLine(int argc, char **argv) const;
  std::vector<mila::SequentialBBPProfilingResults> RunIterations(const Parameters config) const;
  Results PrepareResults(const std::vector<mila::SequentialBBPProfilingResults> &raw_results) const;
  void PrintParameters(const Parameters &config) const;
  void PrintResults(const SequentialBBPProfilingResults &results) const;
  void PrintResultsStatistics(const Results &results) const;

  const std::shared_ptr<mila::Logger> logger_;
};
}  // mila
#endif  //MILA_BBP_SEQUENTIAL_APP_HPP
