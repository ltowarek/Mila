#include "bbp_parallel.h"
#include "bbp_parallel_profiler.h"

mila::OpenCLApplication::~OpenCLApplication() {

}
mila::GenericOpenCLApplication::GenericOpenCLApplication() : GenericOpenCLApplication(0, 0, nullptr) {

}
mila::GenericOpenCLApplication::GenericOpenCLApplication(const size_t platform_id,
                                                         const size_t device_id,
                                                         std::unique_ptr<Logger> logger) : platform_id_(
    platform_id), device_id_(device_id) {
  logger_ = std::move(logger);
}
mila::GenericOpenCLApplication::~GenericOpenCLApplication() {

}
clpp::Program
mila::GenericOpenCLApplication::CreateProgramFromSource(const std::string &source_file_path) const {
  const auto source_file = mila::utils::ReadFile(source_file_path);
  return clpp::Program(context_, source_file);
}
void mila::GenericOpenCLApplication::BuildProgram(const clpp::Program &program,
                                                  const clpp::Device &device) const {
  try {
    program.build(device);
  } catch (const clpp::Error &error) {
    logger_->Critical("%s\n", program.getBuildLog(device).c_str());
  }
}
clpp::Kernel mila::GenericOpenCLApplication::CreateKernel(const std::string &kernel_name,
                                                          const std::string &source_file_path) {
  auto program = CreateProgramFromSource(source_file_path);
  BuildProgram(program, device_);
  return clpp::Kernel(program, kernel_name.c_str());
}
void mila::GenericOpenCLApplication::Initialize() {
  const auto platforms = clpp::Platform::get();
  platform_ = platforms.at(platform_id_);

  const auto devices = platform_.getAllDevices();
  device_ = devices.at(device_id_);

  context_ = clpp::Context(device_);
  queue_ = clpp::Queue(context_, device_, CL_QUEUE_PROFILING_ENABLE);
}
clpp::Platform mila::GenericOpenCLApplication::GetPlatform() const {
  return platform_;
}
std::string mila::GenericOpenCLApplication::GetPlatformName() const {
  return platform_.getName();
}
clpp::Device mila::GenericOpenCLApplication::GetDevice() const {
  return device_;
}
std::string mila::GenericOpenCLApplication::GetDeviceName() const {
  return device_.getName();
}
clpp::Context mila::GenericOpenCLApplication::GetContext() const {
  return context_;
}
clpp::Queue mila::GenericOpenCLApplication::GetQueue() const {
  return queue_;
}

mila::BBP::~BBP() {

}
std::string mila::GenericBBP::GetDigits(const std::vector<float> &digits) const {
  const auto hex_digits = mila::bbp::utils::ConvertFractionsToHex(digits, 1);
  auto output = std::string("");
  for (const auto digit : hex_digits) {
    output += digit[0];
  }
  return output;
}
mila::GenericBBP::~GenericBBP() {

}

mila::ParallelBBP::ParallelBBP() : mila::ParallelBBP(nullptr, nullptr) {

}
mila::ParallelBBP::ParallelBBP(std::unique_ptr<OpenCLApplication> ocl_app,
                               std::unique_ptr<Logger> logger) :
    source_file_path_("bbp.cl"),
    kernel_name_("bbp") {
  logger_ = std::move(logger);
  ocl_app_ = std::move(ocl_app);
}
mila::ParallelBBP::~ParallelBBP() {

}
void mila::ParallelBBP::Initialize() {
  kernel_ = ocl_app_->CreateKernel(kernel_name_, source_file_path_);
}
std::vector<float>
mila::ParallelBBP::ComputeDigits(const size_t number_of_digits, const cl_uint starting_position) {
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
clpp::Buffer mila::ParallelBBP::CreateBuffer(const std::vector<cl_float> output) const {
  return clpp::Buffer(ocl_app_->GetContext(), CL_MEM_WRITE_ONLY, output.size() * sizeof(output.at(0)));
}
mila::ParallelBBP::Events mila::ParallelBBP::GetEvents() const {
  return events_;
}

std::unique_ptr<mila::OpenCLApplication>
mila::OpenCLApplicationFactory::MakeGeneric(const size_t platform_id,
                                            const size_t device_id,
                                            std::unique_ptr<Logger> logger) {
  auto ocl_app = new GenericOpenCLApplication(platform_id, device_id, std::move(logger));
  ocl_app->Initialize();
  return std::unique_ptr<OpenCLApplication>(ocl_app);
}

