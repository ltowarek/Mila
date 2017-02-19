#ifndef MILA_MEAN_SHIFT_IMAGE_PROCESSING_APP_HPP
#define MILA_MEAN_SHIFT_IMAGE_PROCESSING_APP_HPP

#include "plugin.hpp"
#include "mean_shift_image_processing_profiler.hpp"
#include "mean_shift_sequential.hpp"
#include "mean_shift_parallel.hpp"
#include "statistics.hpp"

namespace mila {
class SequentialMeanShiftImageProcessingApp : public Plugin {
 public:
  SequentialMeanShiftImageProcessingApp(const std::shared_ptr<mila::Logger> logger);
  virtual ~SequentialMeanShiftImageProcessingApp();
  virtual void Run(int argc, char **argv) const override;
 private:
  struct Parameters {
    std::string input_file;
    std::string output_file;
    float bandwidth;
    size_t number_of_iterations;
  };

  struct Results {
    std::vector<float> pixels_per_second;
    std::vector<float> mean_shift_image_processing_duration;
  };

  Parameters ParseCommandLine(int argc, char **argv) const;
  std::vector<mila::MeanShiftImageProcessingProfilingResults> RunIterations(const Parameters config) const;
  Results PrepareResults(const std::vector<mila::MeanShiftImageProcessingProfilingResults> &raw_results) const;
  void PrintParameters(const Parameters &config) const;
  void PrintResults(const MeanShiftImageProcessingProfilingResults &results) const;
  void PrintResultsStatistics(const Results &results) const;

  const std::shared_ptr<mila::Logger> logger_;
};

class ParallelMeanShiftImageProcessingApp : public Plugin {
 public:
  ParallelMeanShiftImageProcessingApp(const std::shared_ptr<mila::Logger> logger);
  virtual ~ParallelMeanShiftImageProcessingApp();
  virtual void Run(int argc, char **argv) const override;
 private:
  struct Parameters {
    std::string input_file;
    std::string output_file;
    float bandwidth;
    size_t platform_id;
    size_t device_id;
    size_t number_of_iterations;
  };

  struct Results {
    std::vector<float> pixels_per_second;
    std::vector<float> mean_shift_image_processing_duration;
  };

  Parameters ParseCommandLine(int argc, char **argv) const;
  std::vector<mila::MeanShiftImageProcessingProfilingResults> RunIterations(const Parameters config) const;
  Results PrepareResults(const std::vector<mila::MeanShiftImageProcessingProfilingResults> &raw_results) const;
  void PrintParameters(const Parameters &config) const;
  void PrintResults(const MeanShiftImageProcessingProfilingResults &results) const;
  void PrintResultsStatistics(const Results &results) const;

  const std::shared_ptr<mila::Logger> logger_;
};
}  // mila
#endif  //MILA_MEAN_SHIFT_IMAGE_PROCESSING_APP_HPP
