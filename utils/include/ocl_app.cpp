#include "ocl_app.h"

mila::OpenCLApplication::~OpenCLApplication() {

}
std::unique_ptr<mila::OpenCLApplication>
mila::OpenCLApplicationFactory::MakeGeneric(const size_t platform_id,
                                            const size_t device_id,
                                            std::unique_ptr<mila::Logger> logger) {
  auto ocl_app = new mila::GenericOpenCLApplication(platform_id, device_id, move(logger));
  ocl_app->Initialize();
  return std::unique_ptr<mila::OpenCLApplication>(ocl_app);
}
mila::GenericOpenCLApplication::GenericOpenCLApplication() : GenericOpenCLApplication(0, 0, nullptr) {

}
mila::GenericOpenCLApplication::GenericOpenCLApplication(const size_t platform_id,
                                                         const size_t device_id,
                                                         std::unique_ptr<mila::Logger> logger) : platform_id_(
    platform_id), device_id_(device_id) {
  logger_ = move(logger);
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