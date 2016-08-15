#ifndef MILA_OCL_APP_PROFILER_H
#define MILA_OCL_APP_PROFILER_H

#include <string>
#include <memory>

#include "clpp.h"
#include "ocl_app.h"

namespace mila {
class OpenCLApplicationProfiler: public OpenCLApplication {
 public:
  OpenCLApplicationProfiler();
  OpenCLApplicationProfiler(std::unique_ptr<mila::OpenCLApplication> app);
  virtual void Initialize() override;
  virtual clpp::Program CreateProgramFromSource(const std::string &source_file_path) const override;
  virtual void BuildProgram(const clpp::Program &program, const clpp::Device &device) const override;
  virtual clpp::Kernel CreateKernel(const std::string &kernel_name, const std::string &source_file_path) override;
  virtual clpp::Platform GetPlatform() const override;
  virtual std::string GetPlatformName() const override;
  virtual clpp::Device GetDevice() const override;
  virtual std::string GetDeviceName() const override;
  virtual clpp::Context GetContext() const override;
  virtual clpp::Queue GetQueue() const override;
 private:
  std::unique_ptr<mila::OpenCLApplication> app_;
};
}  // mila

#endif //MILA_OCL_APP_PROFILER_H
