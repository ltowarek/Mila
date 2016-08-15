#include "bbp_parallel_profiler.h"

mila::BBPProfiler::~BBPProfiler() {

}

mila::GenericBBPProfiler::GenericBBPProfiler() : GenericBBPProfiler(nullptr, nullptr, nullptr) {

}
mila::GenericBBPProfiler::GenericBBPProfiler(std::unique_ptr<mila::BBP> bbp,
                                             std::unique_ptr<Profiler> profiler,
                                             std::unique_ptr<Logger> logger)
    : bbp_(std::move(bbp)), profiler_(std::move(profiler)), logger_(std::move(logger)), number_of_digits_(0) {

}
mila::GenericBBPProfiler::~GenericBBPProfiler() {

}
std::vector<float>
mila::GenericBBPProfiler::ComputeDigits(const size_t number_of_digits, const cl_uint starting_position) {
  number_of_digits_ = number_of_digits;
  profiler_->Start("ComputeDigits");
  auto output = bbp_->ComputeDigits(number_of_digits, starting_position);
  profiler_->End("ComputeDigits");
  return output;
}
std::string mila::GenericBBPProfiler::GetDigits(const std::vector<float> &digits) const {
  return bbp_->GetDigits(digits);
}

std::unique_ptr<mila::BBP>
mila::BBPFactory::MakeParallel(std::unique_ptr<OpenCLApplication> ocl_app,
                               std::unique_ptr<Logger> logger) {
  auto bbp = new mila::ParallelBBP(move(ocl_app), move(logger));
  bbp->Initialize();
  return std::unique_ptr<mila::BBP>(bbp);
}
std::unique_ptr<mila::BBP>
mila::BBPFactory::MakeGenericBBPProfiler(std::unique_ptr<mila::BBP> bbp,
                                         std::unique_ptr<Profiler> profiler,
                                         std::unique_ptr<Logger> logger) {
  return std::unique_ptr<mila::BBP>(new mila::GenericBBPProfiler(std::move(bbp),
                                                                 std::move(profiler),
                                                                 std::move(logger)));
}
std::unique_ptr<mila::BBP>
mila::BBPFactory::MakeParallelBBPProfiler(std::unique_ptr<OpenCLApplication> ocl_app,
                                          std::unique_ptr<Profiler> profiler,
                                          std::unique_ptr<Logger> logger) {
  auto bbp = std::unique_ptr<mila::ParallelBBP>(new mila::ParallelBBP(move(ocl_app),
                                                                      move(logger)));
  auto bbp_profiler =
      new mila::ParallelBBPProfiler(std::move(bbp), std::move(profiler), std::move(logger));
  bbp_profiler->Initialize();
  return std::unique_ptr<mila::BBP>(bbp_profiler);
}

std::unique_ptr<mila::BBPProfiler>
mila::BBPProfilerFactory::MakeGeneric(std::unique_ptr<mila::BBP> bbp,
                                      std::unique_ptr<Profiler> profiler,
                                      std::unique_ptr<Logger> logger) {
  return std::unique_ptr<mila::BBPProfiler>(new mila::GenericBBPProfiler(std::move(bbp),
                                                                         std::move(
                                                                             profiler),
                                                                         std::move(
                                                                             logger)));
}
std::unique_ptr<mila::BBPProfiler>
mila::BBPProfilerFactory::MakeParallel(std::unique_ptr<OpenCLApplication> ocl_app,
                                       std::unique_ptr<Profiler> profiler,
                                       std::unique_ptr<Logger> logger) {
  auto bbp = std::unique_ptr<mila::ParallelBBP>(new mila::ParallelBBP(move(ocl_app),
                                                                      move(logger)));
  auto bbp_profiler =
      new mila::ParallelBBPProfiler(std::move(bbp), std::move(profiler), std::move(logger));
  bbp_profiler->Initialize();
  return std::unique_ptr<mila::BBPProfiler>(std::move(bbp_profiler));
}

mila::ParallelBBPProfiler::ParallelBBPProfiler() : ParallelBBPProfiler(nullptr, nullptr, nullptr) {

}
mila::ParallelBBPProfiler::ParallelBBPProfiler(std::unique_ptr<mila::ParallelBBP> bbp,
                                               std::unique_ptr<Profiler> profiler,
                                               std::unique_ptr<Logger> logger)
    : bbp_(std::move(bbp)), profiler_(std::move(profiler)), logger_(std::move(logger)) {

}
mila::ParallelBBPProfiler::~ParallelBBPProfiler() {

}
std::vector<float> mila::ParallelBBPProfiler::ComputeDigits(const size_t number_of_digits,
                                                            const cl_uint starting_position) {
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
        std::chrono::duration_cast<std::chrono::microseconds>(mila::ParallelBBPProfiler::GetProfilingInfo(
            event));
  }
  event = bbp_->GetEvents().read_buffer;
  if (event != nullptr) {
    results_.read_buffer_duration =
        std::chrono::duration_cast<std::chrono::microseconds>(mila::ParallelBBPProfiler::GetProfilingInfo(
            event));
  }

  results_.compute_digits_duration = profiler_->GetDuration("ComputeDigits");
  results_.digits_per_second = mila::utils::GetValuePerSecond(number_of_digits,
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
    auto read_writes = 1;
    auto micro_to_giga = 1e3f;
    gb_per_s = number_of_work_items * sizeof(cl_float) * read_writes / microseconds / micro_to_giga;
  }
  return gb_per_s;
}
std::chrono::duration<long, std::nano>
mila::ParallelBBPProfiler::GetProfilingInfo(clpp::Event event) const {
  return std::chrono::nanoseconds(event.getProfilingCommandEnd() - event.getProfilingCommandStart());
}
mila::ParallelBBPProfilingResults mila::ParallelBBPProfiler::GetResults() const {
  return results_;
}
