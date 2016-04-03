#include "mean_shift_parallel_profiler.h"

mila::meanshift::parallel::MeanShiftProfiler::MeanShiftProfiler(): MeanShift(), main_result_("Run") {

}

mila::meanshift::parallel::MeanShiftProfiler::MeanShiftProfiler(size_t platform_id, size_t device_id): MeanShift(platform_id, device_id), main_result_("Run") {

}

mila::meanshift::parallel::MeanShiftProfiler::MeanShiftProfiler(size_t platform_id,
                                                                size_t device_id,
                                                                float precision,
                                                                size_t max_iterations): MeanShift(platform_id, device_id, precision, max_iterations), main_result_("Run") {

}

void mila::meanshift::parallel::MeanShiftProfiler::Initialize() {
  auto start_time = std::chrono::high_resolution_clock::now();
  MeanShift::Initialize();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("Initialize", duration));
}

std::vector<cl_float4> mila::meanshift::parallel::MeanShiftProfiler::Run(const std::vector<cl_float4> &points,
                                                                         float bandwidth) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = MeanShift::Run(points, bandwidth);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("Run", duration));
  return output;
}

std::string mila::meanshift::parallel::MeanShiftProfiler::main_result() const {
  return main_result_;
}

std::map<std::string, int64_t> mila::meanshift::parallel::MeanShiftProfiler::results() const {
  return results_;
}
