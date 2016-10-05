#include "mean_shift_parallel_profiler.h"

mila::ParallelMeanShiftProfiler::ParallelMeanShiftProfiler(std::unique_ptr<mila::OpenCLApplication> ocl_app,
                                                           const std::shared_ptr<mila::Logger> logger)
    : ParallelMeanShift(std::move(ocl_app), logger) {

}

void mila::ParallelMeanShiftProfiler::Initialize() {
  auto start_time = std::chrono::high_resolution_clock::now();
  ParallelMeanShift::Initialize();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, float>("Initialize", duration));
}

std::vector<mila::Point> mila::ParallelMeanShiftProfiler::Run(const std::vector<Point> &points,
                                                                         float bandwidth) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = ParallelMeanShift::Run(points, bandwidth);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  results_.insert(std::pair<std::string, float>("Run", duration_us));
  results_.insert(std::pair<std::string, float>("Points per second", mila::utils::GetValuePerSecond(points.size(), duration)));

  GetProfilingInfo();
  bandwidth_ = ComputeBandwidthAsGBPS(points.size(), GetEnqueueNDRangeAsMicroseconds());

  return output;
}

size_t mila::ParallelMeanShiftProfiler::GetBuildKernelAsMicroseconds() {
  return device_statistics_.GetBuildKernelAsMicroseconds();
}

size_t mila::ParallelMeanShiftProfiler::GetCopyBufferAsMicroseconds() {
  return device_statistics_.GetCopyBufferAsMicroseconds();
}

size_t mila::ParallelMeanShiftProfiler::GetReadBufferAsMicroseconds() {
  return device_statistics_.GetReadBufferAsMicroseconds();
}

size_t mila::ParallelMeanShiftProfiler::GetEnqueueNDRangeAsMicroseconds() {
  return device_statistics_.GetEnqueueNDRangeAsMicroseconds();
}

std::string mila::ParallelMeanShiftProfiler::GetOpenCLStatisticsAsString() {
  return device_statistics_.GetOpenCLStatisticsAsString();
}

void mila::ParallelMeanShiftProfiler::GetProfilingInfo() {
  if (!events_.copy_buffer.empty()) {
    device_statistics_.SetCopyBufferAsMicroseconds(mila::utils::Sum(GetProfilingInfoAsMicroseconds(events_.copy_buffer)));
  }
  if (!events_.read_buffer_with_distances.empty()) {
    device_statistics_.SetReadBufferAsMicroseconds(mila::utils::Sum(GetProfilingInfoAsMicroseconds(events_.read_buffer_with_distances)));
  }
  if (!events_.enqueue_nd_range.empty()) {
    device_statistics_.SetEnqueueNDRangeAsMicroseconds(mila::utils::Sum(GetProfilingInfoAsMicroseconds(events_.enqueue_nd_range)));
  }
}

size_t mila::ParallelMeanShiftProfiler::GetProfilingInfoAsMicroseconds(clpp::Event event) {
  auto nanoseconds = event.getProfilingCommandEnd() - event.getProfilingCommandStart();
  auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::nanoseconds(nanoseconds));
  return static_cast<size_t>(microseconds.count());
}

std::vector<size_t> mila::ParallelMeanShiftProfiler::GetProfilingInfoAsMicroseconds(const std::vector<clpp::Event>& events) {
  auto output = std::vector<size_t>();
  for (int i = 0; i < events.size(); ++i) {
    output.push_back(GetProfilingInfoAsMicroseconds(events[i]));
  }
  return output;
}

float mila::ParallelMeanShiftProfiler::ComputeBandwidthAsGBPS(size_t number_of_work_items, float microseconds) {
  auto gb_per_s = 0.0f;
  if (microseconds > 0) {
    auto current_points_bytes = sizeof(cl_float4) * number_of_work_items * (number_of_work_items + 1);
    auto original_points_bytes = sizeof(cl_float4) * number_of_work_items * (number_of_work_items * 2);
    auto shifted_points_bytes = sizeof(cl_float4) * number_of_work_items * 2;
    auto distances_bytes = sizeof(cl_float) * number_of_work_items * 1;
    auto micro_to_giga = 1e3f;
    gb_per_s = (current_points_bytes + original_points_bytes + shifted_points_bytes + distances_bytes) / microseconds / micro_to_giga;
  }
  return gb_per_s;
}

float mila::ParallelMeanShiftProfiler::GetBandwidth() {
  return bandwidth_;
}

std::string mila::ParallelMeanShiftProfiler::main_result() const {
  return main_result_;
}

std::string mila::ParallelMeanShiftProfiler::main_duration() const {
  return main_duration_;
}

std::map<std::string, float> mila::ParallelMeanShiftProfiler::results() const {
  return results_;
}
mila::ParallelMeanShiftProfiler::~ParallelMeanShiftProfiler() {

}
