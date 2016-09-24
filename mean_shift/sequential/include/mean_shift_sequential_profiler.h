#ifndef MILA_MEAN_SHIFT_SEQUENTIAL_PROFILER_H_
#define MILA_MEAN_SHIFT_SEQUENTIAL_PROFILER_H_

#include <chrono>
#include <map>
#include <string>

#include "mean_shift_sequential.h"
#include "utils.h"

namespace mila {

class SequentialMeanShiftProfiler: public SequentialMeanShift {
 public:
  SequentialMeanShiftProfiler();

  std::vector<Point> Run(const std::vector<Point> &points, float bandwidth) override;

  std::string main_result() const;
  std::string main_duration() const;
  std::map<std::string, float> results() const;
 private:
  const std::string main_result_;
  const std::string main_duration_;
  std::map<std::string, float> results_;
};

class SequentialMeanShiftImageProcessingProfiler: public SequentialMeanShiftImageProcessing {
 public:
  SequentialMeanShiftImageProcessingProfiler();

  std::vector<Point> Run(const std::vector<Point> &points, float bandwidth) override;
  void Run(const std::string &input_file, const std::string &output_file, float bandwidth) override;

  std::string main_result() const;
  std::string main_duration() const;
  std::map<std::string, float> results() const;
 private:
  const std::string main_result_;
  const std::string main_duration_;
  std::map<std::string, float> results_;
  size_t number_of_points_;
};

}  // mila

#endif  // MILA_MEAN_SHIFT_SEQUENTIAL_PROFILER_H_
