#ifndef MILA_MEAN_SHIFT_SEQUENTIAL_APP_HPP
#define MILA_MEAN_SHIFT_SEQUENTIAL_APP_HPP

#include "plugin.hpp"
#include "mean_shift_sequential_profiler.hpp"
#include "statistics.hpp"

namespace mila {
class SequentialMeanShiftApp : public Plugin {
 public:
  SequentialMeanShiftApp(const std::shared_ptr<mila::Logger> logger);
  virtual ~SequentialMeanShiftApp();
  virtual void Run(int argc, char **argv) const override;
 private:
  struct Parameters {
    std::vector<Point> points;
    float bandwidth;
    size_t number_of_iterations;
  };

  struct Results {
    std::vector<float> points_per_second;
    std::vector<float> mean_shift_duration;
  };

  Parameters ParseCommandLine(int argc, char **argv) const;
  std::vector<mila::SequentialMeanShiftProfilingResults> RunIterations(const Parameters config) const;
  Results PrepareResults(const std::vector<mila::SequentialMeanShiftProfilingResults> &raw_results) const;
  void PrintParameters(const Parameters &config) const;
  void PrintResults(const SequentialMeanShiftProfilingResults &results) const;
  void PrintResultsStatistics(const Results &results) const;

  const std::shared_ptr<mila::Logger> logger_;
};
}  // mila
#endif  //MILA_MEAN_SHIFT_SEQUENTIAL_APP_HPP
