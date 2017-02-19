#ifndef MILA_OCL_APP_H
#define MILA_OCL_APP_H

#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include "clpp.h"
#include "logger.hpp"
#include "utils.hpp"

namespace mila {
class OpenCLApplication {
 public:
  virtual ~OpenCLApplication() = 0;
  virtual void Initialize() = 0;
  virtual clpp::Program CreateProgramFromSource(const std::string &source_file_path) const = 0;
  virtual void BuildProgram(const clpp::Program &program, const clpp::Device &device) const = 0;
  virtual clpp::Kernel CreateKernel(const std::string &kernel_name, const std::string &source_file_path) = 0;

  virtual clpp::Platform GetPlatform() const = 0;
  virtual std::string GetPlatformName() const = 0;
  virtual clpp::Device GetDevice() const = 0;
  virtual std::string GetDeviceName() const = 0;
  virtual clpp::Context GetContext() const = 0;
  virtual clpp::Queue GetQueue() const = 0;
};
class OpenCLApplicationFactory {
 public:
  std::unique_ptr<OpenCLApplication>
  MakeGeneric(const size_t platform_id, const size_t device_id, const std::shared_ptr<mila::Logger> logger);
};
class GenericOpenCLApplication: public OpenCLApplication {
 public:
  GenericOpenCLApplication();
  GenericOpenCLApplication(const size_t platform_id,
                           const size_t device_id,
                           const std::shared_ptr<mila::Logger> logger);
  ~GenericOpenCLApplication();
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
  const std::shared_ptr<mila::Logger> logger_;
  clpp::Platform platform_;
  clpp::Device device_;
  clpp::Context context_;
  clpp::Queue queue_;

  const size_t platform_id_;
  const size_t device_id_;
};
}
#endif //MILA_OCL_APP_H
