#include "mean_shift_sequential_profiler.hpp"

mila::SequentialMeanShiftProfiler::SequentialMeanShiftProfiler(std::unique_ptr<mila::SequentialMeanShift> mean_shift,
                                                               std::unique_ptr<mila::Profiler> profiler,
                                                               const std::shared_ptr<mila::Logger> logger)
    : mean_shift_(std::move(mean_shift)), profiler_(std::move(profiler)), logger_(logger) {
  InitResults();
}
mila::SequentialMeanShiftProfiler::~SequentialMeanShiftProfiler() {

}
mila::SequentialMeanShiftProfilingResults mila::SequentialMeanShiftProfiler::GetResults() const {
  return results_;
}
std::vector<mila::Point> mila::SequentialMeanShiftProfiler::Run(const std::vector<Point> &points,
                                                                const float bandwidth) {
  profiler_->Start("MeanShift");
  const auto output = mean_shift_->Run(points, bandwidth);
  profiler_->End("MeanShift");
  SetResultsAfterComputeDigits(points.size());
  return output;
}
void mila::SequentialMeanShiftProfiler::InitResults() {
  results_.mean_shift_duration = std::chrono::seconds(0);
  results_.points_per_second = 0.0f;
}
void mila::SequentialMeanShiftProfiler::SetResultsAfterComputeDigits(const size_t number_of_points) {
  results_.mean_shift_duration = profiler_->GetDuration("MeanShift");
  results_.points_per_second = mila::GetValuePerSecond(number_of_points,
                                                       results_.mean_shift_duration);
}
