#include "bbp_sequential_profiler.hpp"
#include "utils.hpp"

mila::SequentialBBPProfiler::SequentialBBPProfiler(std::unique_ptr<mila::SequentialBBP> bbp,
                                                   std::unique_ptr<mila::Profiler> profiler,
                                                   const std::shared_ptr<mila::Logger> logger)
    : bbp_(std::move(bbp)), profiler_(std::move(profiler)), logger_(logger) {
  InitResults();
}
mila::SequentialBBPProfiler::~SequentialBBPProfiler() {

}
std::vector<float>
mila::SequentialBBPProfiler::ComputeDigits(const size_t number_of_digits, const size_t starting_position) {
  profiler_->Start("ComputeDigits");
  auto output = bbp_->ComputeDigits(number_of_digits, starting_position);
  profiler_->End("ComputeDigits");
  SetResultsAfterComputeDigits(number_of_digits);
  return output;
}
std::string mila::SequentialBBPProfiler::GetDigits(const std::vector<float> &digits) const {
  return bbp_->GetDigits(digits);
}
mila::SequentialBBPProfilingResults mila::SequentialBBPProfiler::GetResults() const {
  return results_;
}
void mila::SequentialBBPProfiler::SetResultsAfterComputeDigits(const size_t number_of_digits) {
  results_.compute_digits_duration = profiler_->GetDuration("ComputeDigits");
  results_.digits_per_second = mila::GetValuePerSecond(number_of_digits,
                                                       results_.compute_digits_duration);
}
void mila::SequentialBBPProfiler::InitResults() {
  results_.compute_digits_duration = std::chrono::seconds(0);
  results_.digits_per_second = 0.0f;
}
