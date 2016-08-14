#include "bbp_parallel_profiler.h"

mila::bbp::parallel::OpenCLApplicationProfiler::OpenCLApplicationProfiler() : OpenCLApplicationProfiler(nullptr) {

}
mila::bbp::parallel::OpenCLApplicationProfiler::OpenCLApplicationProfiler(std::unique_ptr<mila::bbp::parallel::OpenCLApplication> app) {
  app_ = std::move(app);
}
void mila::bbp::parallel::OpenCLApplicationProfiler::Initialize() {
  app_->Initialize();
}
clpp::Program
mila::bbp::parallel::OpenCLApplicationProfiler::CreateProgramFromSource(const std::string &source_file_path) const {
  return app_->CreateProgramFromSource(source_file_path);
}
void mila::bbp::parallel::OpenCLApplicationProfiler::BuildProgram(const clpp::Program &program,
                                                                  const clpp::Device &device) const {
  app_->BuildProgram(program, device);
}
clpp::Kernel mila::bbp::parallel::OpenCLApplicationProfiler::CreateKernel(const std::string &kernel_name,
                                                                          const std::string &source_file_path) {
  return app_->CreateKernel(kernel_name, source_file_path);
}
clpp::Platform mila::bbp::parallel::OpenCLApplicationProfiler::GetPlatform() const {
  return app_->GetPlatform();
}
std::string mila::bbp::parallel::OpenCLApplicationProfiler::GetPlatformName() const {
  return app_->GetPlatformName();
}
clpp::Device mila::bbp::parallel::OpenCLApplicationProfiler::GetDevice() const {
  return app_->GetDevice();
}
std::string mila::bbp::parallel::OpenCLApplicationProfiler::GetDeviceName() const {
  return app_->GetDeviceName();
}
clpp::Context mila::bbp::parallel::OpenCLApplicationProfiler::GetContext() const {
  return app_->GetContext();
}
clpp::Queue mila::bbp::parallel::OpenCLApplicationProfiler::GetQueue() const {
  return app_->GetQueue();
}

mila::bbp::parallel::BBPProfilerInterface::~BBPProfilerInterface() {

}

mila::bbp::parallel::BBPProfiler::BBPProfiler() : BBPProfiler(nullptr, nullptr, nullptr) {

}
mila::bbp::parallel::BBPProfiler::BBPProfiler(std::unique_ptr<mila::bbp::parallel::BBP> bbp,
                                              std::unique_ptr<mila::bbp::parallel::Profiler> profiler,
                                              std::unique_ptr<mila::bbp::parallel::Logger> logger)
    : bbp_(std::move(bbp)), profiler_(std::move(profiler)), logger_(std::move(logger)), number_of_digits_(0) {

}
mila::bbp::parallel::BBPProfiler::~BBPProfiler() {

}
std::vector<float>
mila::bbp::parallel::BBPProfiler::ComputeDigits(const size_t number_of_digits, const cl_uint starting_position) {
  number_of_digits_ = number_of_digits;
  profiler_->Start("ComputeDigits");
  auto output = bbp_->ComputeDigits(number_of_digits, starting_position);
  profiler_->End("ComputeDigits");
  return output;
}
std::string mila::bbp::parallel::BBPProfiler::GetDigits(const std::vector<float> &digits) const {
  return bbp_->GetDigits(digits);
}
std::chrono::duration<float, std::micro> mila::bbp::parallel::BBPProfiler::ComputeDigitsDuration() const {
  return profiler_->GetDuration("ComputeDigits");
}
float mila::bbp::parallel::BBPProfiler::GetDigitsPerSecond() const {
  return mila::utils::GetValuePerSecond(number_of_digits_, ComputeDigitsDuration());
}

std::unique_ptr<mila::bbp::parallel::BBP>
mila::bbp::parallel::BBPFactory::MakeParallel(std::unique_ptr<mila::bbp::parallel::OpenCLApplication> ocl_app,
                                              std::unique_ptr<mila::bbp::parallel::Logger> logger) {
  auto bbp = new mila::bbp::parallel::ParallelBBP(move(ocl_app), move(logger));
  bbp->Initialize();
  return std::unique_ptr<mila::bbp::parallel::BBP>(bbp);
}
std::unique_ptr<mila::bbp::parallel::BBP>
mila::bbp::parallel::BBPFactory::MakeBBPProfiler(std::unique_ptr<mila::bbp::parallel::BBP> bbp,
                                                 std::unique_ptr<mila::bbp::parallel::Profiler> profiler,
                                                 std::unique_ptr<mila::bbp::parallel::Logger> logger) {
  return std::unique_ptr<mila::bbp::parallel::BBP>(new mila::bbp::parallel::BBPProfiler(std::move(bbp),
                                                                                        std::move(profiler),
                                                                                        std::move(logger)));
}
std::unique_ptr<mila::bbp::parallel::BBP>
mila::bbp::parallel::BBPFactory::MakeParallelBBPProfiler(std::unique_ptr<mila::bbp::parallel::OpenCLApplication> ocl_app,
                                                         std::unique_ptr<mila::bbp::parallel::Profiler> profiler,
                                                         std::unique_ptr<mila::bbp::parallel::Logger> logger) {
  auto bbp = std::unique_ptr<mila::bbp::parallel::ParallelBBP>(new mila::bbp::parallel::ParallelBBP(move(ocl_app),
                                                                                                    move(logger)));
  auto bbp_profiler =
      new mila::bbp::parallel::ParallelBBPProfiler(std::move(bbp), std::move(profiler), std::move(logger));
  bbp_profiler->Initialize();
  return std::unique_ptr<mila::bbp::parallel::BBP>(bbp_profiler);
}

std::unique_ptr<mila::bbp::parallel::Profiler>
mila::bbp::parallel::ProfilerFactory::MakeChrono(std::unique_ptr<mila::bbp::parallel::Logger> logger) {
  return std::unique_ptr<mila::bbp::parallel::Profiler>(new ChronoProfiler(std::move(logger)));
}

std::unique_ptr<mila::bbp::parallel::BBPProfilerInterface>
mila::bbp::parallel::BBPProfilerInterfaceFactory::MakeGeneric(std::unique_ptr<mila::bbp::parallel::BBP> bbp,
                                                              std::unique_ptr<mila::bbp::parallel::Profiler> profiler,
                                                              std::unique_ptr<mila::bbp::parallel::Logger> logger) {
  return std::unique_ptr<mila::bbp::parallel::BBPProfilerInterface>(new mila::bbp::parallel::BBPProfiler(std::move(bbp),
                                                                                                         std::move(
                                                                                                             profiler),
                                                                                                         std::move(
                                                                                                             logger)));
}
std::unique_ptr<mila::bbp::parallel::BBPProfilerInterface>
mila::bbp::parallel::BBPProfilerInterfaceFactory::MakeParallel(std::unique_ptr<mila::bbp::parallel::OpenCLApplication> ocl_app,
                                                               std::unique_ptr<mila::bbp::parallel::Profiler> profiler,
                                                               std::unique_ptr<mila::bbp::parallel::Logger> logger) {
  auto bbp = std::unique_ptr<mila::bbp::parallel::ParallelBBP>(new mila::bbp::parallel::ParallelBBP(move(ocl_app),
                                                                                                    move(logger)));
  auto bbp_profiler =
      new mila::bbp::parallel::ParallelBBPProfiler(std::move(bbp), std::move(profiler), std::move(logger));
  bbp_profiler->Initialize();
  return std::unique_ptr<mila::bbp::parallel::BBPProfilerInterface>(std::move(bbp_profiler));
}

mila::bbp::parallel::ParallelBBPProfiler::ParallelBBPProfiler() : ParallelBBPProfiler(nullptr, nullptr, nullptr) {

}
mila::bbp::parallel::ParallelBBPProfiler::ParallelBBPProfiler(std::unique_ptr<mila::bbp::parallel::ParallelBBP> bbp,
                                                              std::unique_ptr<mila::bbp::parallel::Profiler> profiler,
                                                              std::unique_ptr<mila::bbp::parallel::Logger> logger)
    : bbp_(std::move(bbp)), profiler_(std::move(profiler)), logger_(std::move(logger)) {

}
mila::bbp::parallel::ParallelBBPProfiler::~ParallelBBPProfiler() {

}
std::vector<float> mila::bbp::parallel::ParallelBBPProfiler::ComputeDigits(const size_t number_of_digits,
                                                                           const cl_uint starting_position) {
  profiler_->Start("ComputeDigits");
  auto output = bbp_->ComputeDigits(number_of_digits, starting_position);
  profiler_->End("ComputeDigits");
  SetResultsAfterComputeDigits(number_of_digits);
  return output;
}
void mila::bbp::parallel::ParallelBBPProfiler::SetResultsAfterComputeDigits(const size_t number_of_digits) {
  auto event = bbp_->GetEvents().enqueue_nd_range;
  if (event != nullptr) {
    results_.enqueue_nd_range_duration =
        std::chrono::duration_cast<std::chrono::microseconds>(mila::bbp::parallel::ParallelBBPProfiler::GetProfilingInfo(
            event));
  }
  event = bbp_->GetEvents().read_buffer;
  if (event != nullptr) {
    results_.read_buffer_duration =
        std::chrono::duration_cast<std::chrono::microseconds>(mila::bbp::parallel::ParallelBBPProfiler::GetProfilingInfo(
            event));
  }

  results_.compute_digits_duration = profiler_->GetDuration("ComputeDigits");
  results_.digits_per_second = mila::utils::GetValuePerSecond(number_of_digits,
                                                              mila::bbp::parallel::ParallelBBPProfiler::ComputeDigitsDuration());
  results_.bandwidth = mila::bbp::parallel::ParallelBBPProfiler::ComputeBandwidthAsGBPS(number_of_digits_,
                                                                                        results_.compute_digits_duration.count());
}
std::string mila::bbp::parallel::ParallelBBPProfiler::GetDigits(const std::vector<float> &digits) const {
  return bbp_->GetDigits(digits);
}
std::chrono::duration<float, std::micro> mila::bbp::parallel::ParallelBBPProfiler::ComputeDigitsDuration() const {
  return profiler_->GetDuration("ComputeDigits");
}
float mila::bbp::parallel::ParallelBBPProfiler::GetDigitsPerSecond() const {
  return mila::utils::GetValuePerSecond(number_of_digits_, ComputeDigitsDuration());
}
void mila::bbp::parallel::ParallelBBPProfiler::Initialize() {
  profiler_->Start("Initialize");
  bbp_->Initialize();
  profiler_->End("Initialize");
  SetResultsAfterInitialize();
}
void mila::bbp::parallel::ParallelBBPProfiler::SetResultsAfterInitialize() {
  results_.initialize_duration = profiler_->GetDuration("Initialize");
}
std::chrono::duration<float, std::micro> mila::bbp::parallel::ParallelBBPProfiler::InitializeDuration() const {
  return profiler_->GetDuration("Initialize");
}
float
mila::bbp::parallel::ParallelBBPProfiler::ComputeBandwidthAsGBPS(size_t number_of_work_items, long microseconds) const {
  auto gb_per_s = 0.0f;
  if (microseconds > 0) {
    auto read_writes = 1;
    auto micro_to_giga = 1e3f;
    gb_per_s = number_of_work_items * sizeof(cl_float) * read_writes / microseconds / micro_to_giga;
  }
  return gb_per_s;
}
std::chrono::duration<long, std::nano>
mila::bbp::parallel::ParallelBBPProfiler::GetProfilingInfo(clpp::Event event) const {
  return std::chrono::nanoseconds(event.getProfilingCommandEnd() - event.getProfilingCommandStart());
}
mila::bbp::parallel::ParallelBBPProfilingResults mila::bbp::parallel::ParallelBBPProfiler::GetResults() const {
  return results_;
}
