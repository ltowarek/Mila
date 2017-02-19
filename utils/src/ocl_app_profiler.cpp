#include "ocl_app_profiler.hpp"

mila::OpenCLApplicationProfiler::OpenCLApplicationProfiler() : OpenCLApplicationProfiler(nullptr) {

}
mila::OpenCLApplicationProfiler::OpenCLApplicationProfiler(std::unique_ptr<mila::OpenCLApplication> app) {
  app_ = move(app);
}
void mila::OpenCLApplicationProfiler::Initialize() {
  app_->Initialize();
}
clpp::Program
mila::OpenCLApplicationProfiler::CreateProgramFromSource(const std::string &source_file_path) const {
  return app_->CreateProgramFromSource(source_file_path);
}
void mila::OpenCLApplicationProfiler::BuildProgram(const clpp::Program &program,
                                                   const clpp::Device &device) const {
  app_->BuildProgram(program, device);
}
clpp::Kernel mila::OpenCLApplicationProfiler::CreateKernel(const std::string &kernel_name,
                                                           const std::string &source_file_path) {
  return app_->CreateKernel(kernel_name, source_file_path);
}
clpp::Platform mila::OpenCLApplicationProfiler::GetPlatform() const {
  return app_->GetPlatform();
}
std::string mila::OpenCLApplicationProfiler::GetPlatformName() const {
  return app_->GetPlatformName();
}
clpp::Device mila::OpenCLApplicationProfiler::GetDevice() const {
  return app_->GetDevice();
}
std::string mila::OpenCLApplicationProfiler::GetDeviceName() const {
  return app_->GetDeviceName();
}
clpp::Context mila::OpenCLApplicationProfiler::GetContext() const {
  return app_->GetContext();
}
clpp::Queue mila::OpenCLApplicationProfiler::GetQueue() const {
  return app_->GetQueue();
}