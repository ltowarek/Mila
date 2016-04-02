#ifndef MILA_MEAN_SHIFT_SEQUENTIAL_PROFILER_H_
#define MILA_MEAN_SHIFT_SEQUENTIAL_PROFILER_H_

#include <chrono>
#include <map>
#include <string>

#include "mean_shift_sequential.h"

namespace mila {
namespace meanshift {
namespace sequential {

class MeanShiftProfiler: public MeanShift {
 public:
  MeanShiftProfiler();
  MeanShiftProfiler(float precision, size_t max_iterations);

  std::vector<Point> Run(const std::vector<Point> &points, float bandwidth) override;

  std::string main_result() const;
  std::map<std::string, int64_t> results() const;
 private:
  const std::string main_result_;
  std::map<std::string, int64_t> results_;
};

class MeanShiftImageProcessingProfiler: public MeanShiftImageProcessing {
 public:
  MeanShiftImageProcessingProfiler();
  MeanShiftImageProcessingProfiler(float precision, size_t max_iterations);

  std::vector<Point> Run(const std::vector<Point> &points, float bandwidth) override;
  void Run(const std::string &input_file, const std::string &output_file, float bandwidth) override;

  std::string main_result() const;
  std::map<std::string, int64_t> results() const;
 private:
  const std::string main_result_;
  std::map<std::string, int64_t> results_;
};

}  // sequential
}  // meanshift
}  // mila

#endif  // MILA_MEAN_SHIFT_SEQUENTIAL_PROFILER_H_
