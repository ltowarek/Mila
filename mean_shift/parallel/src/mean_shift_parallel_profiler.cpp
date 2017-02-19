#include "mean_shift_parallel_profiler.hpp"

mila::ParallelMeanShiftProfiler::ParallelMeanShiftProfiler(std::unique_ptr<mila::ParallelMeanShift> mean_shift,
                                                           std::unique_ptr<mila::Profiler> profiler,
                                                           const std::shared_ptr<mila::Logger> logger)
    : mean_shift_(std::move(mean_shift)), profiler_(std::move(profiler)), logger_(logger) {
  InitResults();
}

mila::ParallelMeanShiftProfiler::~ParallelMeanShiftProfiler() {

}

void mila::ParallelMeanShiftProfiler::Initialize() {
  profiler_->Start("Initialize");
  mean_shift_->Initialize();
  profiler_->End("Initialize");
  SetResultsAfterInitialize();
}

std::vector<mila::Point> mila::ParallelMeanShiftProfiler::Run(const std::vector<Point> &points,
                                                              const float bandwidth) {
  profiler_->Start("Run");
  const auto output = mean_shift_->Run(points, bandwidth);
  profiler_->End("Run");
  SetResultsAfterRun(points.size());
  return output;
}

float mila::ParallelMeanShiftProfiler::ComputeBandwidthAsGBPS(const size_t number_of_work_items,
                                                              const float microseconds) {
  auto gb_per_s = 0.0f;
  if (microseconds > 0) {
    const auto current_points_bytes = sizeof(cl_float4) * number_of_work_items * (number_of_work_items + 1);
    const auto original_points_bytes = sizeof(cl_float4) * number_of_work_items * (number_of_work_items * 2);
    const auto shifted_points_bytes = sizeof(cl_float4) * number_of_work_items * 2;
    const auto distances_bytes = sizeof(cl_float) * number_of_work_items * 1;
    const auto micro_to_giga = 1e3f;
    gb_per_s = (current_points_bytes + original_points_bytes + shifted_points_bytes + distances_bytes) / microseconds
        / micro_to_giga;
  }
  return gb_per_s;
}

void mila::ParallelMeanShiftProfiler::InitResults() {
  results_.initialize_duration = std::chrono::seconds(0);
  results_.mean_shift_duration = std::chrono::seconds(0);
  results_.enqueue_nd_range_durations = std::vector<std::chrono::microseconds>(0);
  results_.copy_buffer_durations = std::vector<std::chrono::microseconds>(0);
  results_.read_buffer_with_distances_durations = std::vector<std::chrono::microseconds>(0);
  results_.read_buffer_with_output_duration = std::chrono::seconds(0);
  results_.bandwidth = 0.0f;
  results_.points_per_second = 0.0f;
}

mila::ParallelMeanShiftProfilingResults mila::ParallelMeanShiftProfiler::GetResults() const {
  return results_;
}

void mila::ParallelMeanShiftProfiler::SetResultsAfterInitialize() {
  results_.initialize_duration = profiler_->GetDuration("Initialize");
}

void mila::ParallelMeanShiftProfiler::SetResultsAfterRun(const size_t number_of_points) {
  results_.enqueue_nd_range_durations =
      mila::utils::GetProfilingInfo<std::chrono::microseconds>(mean_shift_->GetEvents().enqueue_nd_range);
  results_.copy_buffer_durations =
      mila::utils::GetProfilingInfo<std::chrono::microseconds>(mean_shift_->GetEvents().copy_buffer);
  results_.read_buffer_with_distances_durations =
      mila::utils::GetProfilingInfo<std::chrono::microseconds>(mean_shift_->GetEvents().read_buffer_with_distances);
  results_.read_buffer_with_output_duration =
      mila::utils::GetProfilingInfo<std::chrono::microseconds>(mean_shift_->GetEvents().read_buffer_with_output);

  results_.mean_shift_duration = profiler_->GetDuration("Run");
  results_.points_per_second = mila::utils::GetValuePerSecond(number_of_points,
                                                              results_.mean_shift_duration);
  results_.bandwidth = ComputeBandwidthAsGBPS(number_of_points, results_.mean_shift_duration.count());
}
