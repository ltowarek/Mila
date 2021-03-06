#include "bbp_parallel_profiler.hpp"

mila::ParallelBBPProfiler::ParallelBBPProfiler() : ParallelBBPProfiler(nullptr, nullptr, nullptr) {

}
mila::ParallelBBPProfiler::ParallelBBPProfiler(std::unique_ptr<mila::ParallelBBP> bbp,
                                               std::unique_ptr<Profiler> profiler,
                                               const std::shared_ptr<Logger> logger)
    : bbp_(std::move(bbp)), profiler_(std::move(profiler)), logger_(logger) {
  InitResults();
}
mila::ParallelBBPProfiler::~ParallelBBPProfiler() {

}
std::vector<float> mila::ParallelBBPProfiler::ComputeDigits(const size_t number_of_digits,
                                                            const size_t starting_position) {
  profiler_->Start("ComputeDigits");
  auto output = bbp_->ComputeDigits(number_of_digits, starting_position);
  profiler_->End("ComputeDigits");
  SetResultsAfterComputeDigits(number_of_digits);
  return output;
}
void mila::ParallelBBPProfiler::SetResultsAfterComputeDigits(const size_t number_of_digits) {
  auto event = bbp_->GetEvents().enqueue_nd_range;
  if (event != nullptr) {
    results_.enqueue_nd_range_duration =
        std::chrono::duration_cast<std::chrono::microseconds>(mila::GetProfilingInfo(
            event));
  }
  event = bbp_->GetEvents().read_buffer;
  if (event != nullptr) {
    results_.read_buffer_duration =
        std::chrono::duration_cast<std::chrono::microseconds>(mila::GetProfilingInfo(
            event));
  }

  results_.compute_digits_duration = profiler_->GetDuration("ComputeDigits");
  results_.digits_per_second = mila::GetValuePerSecond(number_of_digits,
                                                       results_.compute_digits_duration);
  results_.bandwidth = mila::ParallelBBPProfiler::ComputeBandwidthAsGBPS(number_of_digits,
                                                                         results_.compute_digits_duration.count());
}
std::string mila::ParallelBBPProfiler::GetDigits(const std::vector<float> &digits) const {
  return bbp_->GetDigits(digits);
}
void mila::ParallelBBPProfiler::Initialize() {
  profiler_->Start("Initialize");
  bbp_->Initialize();
  profiler_->End("Initialize");
  SetResultsAfterInitialize();
}
void mila::ParallelBBPProfiler::SetResultsAfterInitialize() {
  results_.initialize_duration = profiler_->GetDuration("Initialize");
}
float
mila::ParallelBBPProfiler::ComputeBandwidthAsGBPS(size_t number_of_work_items, long microseconds) const {
  auto gb_per_s = 0.0f;
  if (microseconds > 0) {
    auto read_writes = 1.0f;
    auto micro_to_giga = 1e3f;
    gb_per_s = number_of_work_items * sizeof(cl_float) * read_writes / static_cast<float>(microseconds) / micro_to_giga;
  }
  return gb_per_s;
}
mila::ParallelBBPProfilingResults mila::ParallelBBPProfiler::GetResults() const {
  return results_;
}
void mila::ParallelBBPProfiler::InitResults() {
  results_.enqueue_nd_range_duration = std::chrono::seconds(0);
  results_.initialize_duration = std::chrono::seconds(0);
  results_.read_buffer_duration = std::chrono::seconds(0);
  results_.compute_digits_duration = std::chrono::seconds(0);
  results_.bandwidth = 0.0f;
  results_.digits_per_second = 0.0f;
}
