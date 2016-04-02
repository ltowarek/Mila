#include "mean_shift_sequential_profiler.h"

mila::meanshift::sequential::MeanShiftProfiler::MeanShiftProfiler() : MeanShift(), main_result_("Run") {
}

mila::meanshift::sequential::MeanShiftProfiler::MeanShiftProfiler(float precision, size_t max_iterations) : MeanShift(precision, max_iterations), main_result_("Run") {
}

std::string mila::meanshift::sequential::MeanShiftProfiler::main_result() const {
  return main_result_;
}

std::map<std::string, int64_t> mila::meanshift::sequential::MeanShiftProfiler::results() const {
  return results_;
}

std::vector<mila::meanshift::sequential::Point> mila::meanshift::sequential::MeanShiftProfiler::Run(const std::vector<Point> &points, float bandwidth) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = MeanShift::Run(points, bandwidth);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("Run", duration));
  return output;
}
