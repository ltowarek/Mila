#ifndef MILA_MEAN_SHIFT_IMAGE_PROCESSING_APP_H_
#define MILA_MEAN_SHIFT_IMAGE_PROCESSING_APP_H_

#include "mean_shift_image_processing_profiler.h"
#include "mean_shift_sequential.h"
#include "mean_shift_parallel.h"
#include "statistics.h"

namespace mila {
class SequentialMeanShiftImageProcessingApp : public MeanShiftApp {
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

class ParallelMeanShiftImageProcessingApp : public MeanShiftApp {
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
#endif  //MILA_MEAN_SHIFT_IMAGE_PROCESSING_APP_H_
