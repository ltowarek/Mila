#include "bbp_parallel.h"
#include "bbp_parallel_profiler.h"

mila::bbp::parallel::OpenCLApplication::~OpenCLApplication() {

}
mila::bbp::parallel::GenericOpenCLApplication::GenericOpenCLApplication() : GenericOpenCLApplication(0, 0, nullptr) {

}
mila::bbp::parallel::GenericOpenCLApplication::GenericOpenCLApplication(const size_t platform_id,
                                                                        const size_t device_id,
                                                                        std::unique_ptr<Logger> logger) : platform_id_(
    platform_id), device_id_(device_id) {
  logger_ = std::move(logger);
}
mila::bbp::parallel::GenericOpenCLApplication::~GenericOpenCLApplication() {

}
clpp::Program
mila::bbp::parallel::GenericOpenCLApplication::CreateProgramFromSource(const std::string &source_file_path) const {
  const auto source_file = mila::utils::ReadFile(source_file_path);
  return clpp::Program(context_, source_file);
}
void mila::bbp::parallel::GenericOpenCLApplication::BuildProgram(const clpp::Program &program,
                                                                 const clpp::Device &device) const {
  try {
    program.build(device);
  } catch (const clpp::Error &error) {
    logger_->Critical("%s\n", program.getBuildLog(device).c_str());
  }
}
clpp::Kernel mila::bbp::parallel::GenericOpenCLApplication::CreateKernel(const std::string &kernel_name,
                                                                         const std::string &source_file_path) {
  auto program = CreateProgramFromSource(source_file_path);
  BuildProgram(program, device_);
  return clpp::Kernel(program, kernel_name.c_str());
}
void mila::bbp::parallel::GenericOpenCLApplication::Initialize() {
  const auto platforms = clpp::Platform::get();
  platform_ = platforms.at(platform_id_);

  const auto devices = platform_.getAllDevices();
  device_ = devices.at(device_id_);

  context_ = clpp::Context(device_);
  queue_ = clpp::Queue(context_, device_, CL_QUEUE_PROFILING_ENABLE);
}
clpp::Platform mila::bbp::parallel::GenericOpenCLApplication::GetPlatform() const {
  return platform_;
}
std::string mila::bbp::parallel::GenericOpenCLApplication::GetPlatformName() const {
  return platform_.getName();
}
clpp::Device mila::bbp::parallel::GenericOpenCLApplication::GetDevice() const {
  return device_;
}
std::string mila::bbp::parallel::GenericOpenCLApplication::GetDeviceName() const {
  return device_.getName();
}
clpp::Context mila::bbp::parallel::GenericOpenCLApplication::GetContext() const {
  return context_;
}
clpp::Queue mila::bbp::parallel::GenericOpenCLApplication::GetQueue() const {
  return queue_;
}

mila::bbp::parallel::BBP::~BBP() {

}
std::string mila::bbp::parallel::GenericBBP::GetDigits(const std::vector<float> &digits) const {
  const auto hex_digits = mila::bbp::utils::ConvertFractionsToHex(digits, 1);
  auto output = std::string("");
  for (const auto digit : hex_digits) {
    output += digit[0];
  }
  return output;
}
mila::bbp::parallel::GenericBBP::~GenericBBP() {

}

mila::bbp::parallel::ParallelBBP::ParallelBBP() : mila::bbp::parallel::ParallelBBP(nullptr, nullptr) {

}
mila::bbp::parallel::ParallelBBP::ParallelBBP(std::unique_ptr<OpenCLApplication> ocl_app,
                                              std::unique_ptr<Logger> logger) :
    source_file_path_("bbp.cl"),
    kernel_name_("bbp") {
  logger_ = std::move(logger);
  ocl_app_ = std::move(ocl_app);
}
mila::bbp::parallel::ParallelBBP::~ParallelBBP() {

}
void mila::bbp::parallel::ParallelBBP::Initialize() {
  kernel_ = ocl_app_->CreateKernel(kernel_name_, source_file_path_);
}
std::vector<float>
mila::bbp::parallel::ParallelBBP::ComputeDigits(const size_t number_of_digits, const cl_uint starting_position) {
  auto output = std::vector<cl_float>(number_of_digits, 0.0f);

  if (number_of_digits == 0) {
    return output;
  }

  auto output_buffer = CreateBuffer(output);
  kernel_.setArgs(starting_position, output_buffer);
  const auto global_work_size = std::vector<size_t>{number_of_digits};
  events_.enqueue_nd_range = ocl_app_->GetQueue().enqueueNDRangeKernel(kernel_, global_work_size);
  events_.read_buffer = ocl_app_->GetQueue().enqueueReadBuffer(output_buffer,
                                                               0,
                                                               output.size() * sizeof(output.at(0)),
                                                               output.data(),
                                                               {events_.enqueue_nd_range});

  return output;
}
clpp::Buffer mila::bbp::parallel::ParallelBBP::CreateBuffer(const std::vector<cl_float> output) const {
  return clpp::Buffer(ocl_app_->GetContext(), CL_MEM_WRITE_ONLY, output.size() * sizeof(output.at(0)));
}
mila::bbp::parallel::ParallelBBP::Events mila::bbp::parallel::ParallelBBP::GetEvents() const {
  return events_;
}

std::unique_ptr<mila::bbp::parallel::OpenCLApplication>
mila::bbp::parallel::OpenCLApplicationFactory::MakeGeneric(const size_t platform_id,
                                                           const size_t device_id,
                                                           std::unique_ptr<mila::bbp::parallel::Logger> logger) {
  auto ocl_app = new GenericOpenCLApplication(platform_id, device_id, std::move(logger));
  ocl_app->Initialize();
  return std::unique_ptr<OpenCLApplication>(ocl_app);
}

mila::bbp::parallel::Profiler::~Profiler() {

}

mila::bbp::parallel::ChronoProfiler::~ChronoProfiler() {

}
void mila::bbp::parallel::ChronoProfiler::Start(const std::string &event_name) {
  durations_[event_name] =
      std::pair<std::chrono::high_resolution_clock::time_point, std::chrono::high_resolution_clock::time_point>();
  durations_[event_name].first = std::chrono::high_resolution_clock::now();
}
void mila::bbp::parallel::ChronoProfiler::End(const std::string &event_name) {
  durations_[event_name].second = std::chrono::high_resolution_clock::now();
}
std::chrono::duration<long int, std::micro>
mila::bbp::parallel::ChronoProfiler::GetDuration(const std::string &event_name) const {
  auto duration = std::chrono::microseconds(0);
  if (durations_.count(event_name) > 0) {
    duration = std::chrono::duration_cast<std::chrono::microseconds>(
        durations_.at(event_name).second - durations_.at(event_name).first);
  }
  return duration;
}
mila::bbp::parallel::ChronoProfiler::ChronoProfiler() : ChronoProfiler(nullptr) {

}
mila::bbp::parallel::ChronoProfiler::ChronoProfiler(std::unique_ptr<mila::bbp::parallel::Logger> logger)
    : logger_(std::move(logger)) {

}
