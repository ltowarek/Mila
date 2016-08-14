#ifndef MILA_BBP_PARALLEL_H_
#define MILA_BBP_PARALLEL_H_

#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <memory>

#include "clpp.h"

#include "bbp_utils.h"
#include "utils.h"

namespace mila {
namespace bbp {
namespace parallel {

class Logger {
 public:
  virtual ~Logger() = 0;
  virtual void Critical(const char *message, ...) const = 0;
  virtual void Error(const char *message, ...) const = 0;
  virtual void Warning(const char *message, ...) const = 0;
  virtual void Info(const char *message, ...) const = 0;
  virtual void Debug(const char *message, ...) const = 0;
};

class Profiler {
 public:
  virtual ~Profiler() = 0;
  virtual void Start(const std::string &event_name) = 0;
  virtual void End(const std::string &event_name) = 0;
  virtual std::chrono::duration<long int, std::micro> GetDuration(const std::string &event_name) const = 0;
};

class ChronoProfiler: public Profiler {
 public:
  ChronoProfiler();
  explicit ChronoProfiler(std::unique_ptr<mila::bbp::parallel::Logger> logger);
  virtual ~ChronoProfiler() override;
  virtual void Start(const std::string &event_name) override;
  virtual void End(const std::string &event_name) override;
  virtual std::chrono::duration<long int, std::micro> GetDuration(const std::string &event_name) const override;
 private:
  std::unique_ptr<mila::bbp::parallel::Logger> logger_;
  std::map<std::string,
           std::pair<std::chrono::high_resolution_clock::time_point, std::chrono::high_resolution_clock::time_point>>
      durations_;
};

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
  std::unique_ptr<mila::bbp::parallel::OpenCLApplication>
  MakeGeneric(const size_t platform_id, const size_t device_id, std::unique_ptr<mila::bbp::parallel::Logger> logger);
};

class GenericOpenCLApplication: public OpenCLApplication {
 public:
  GenericOpenCLApplication();
  GenericOpenCLApplication(const size_t platform_id,
                           const size_t device_id,
                           std::unique_ptr<Logger> logger);
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
  std::unique_ptr<Logger> logger_;
  clpp::Platform platform_;
  clpp::Device device_;
  clpp::Context context_;
  clpp::Queue queue_;

  const size_t platform_id_;
  const size_t device_id_;
};

class BBP {
 public:
  virtual ~BBP() = 0;
  virtual std::vector<float> ComputeDigits(const size_t number_of_digits, const cl_uint starting_position) = 0;
  virtual std::string GetDigits(const std::vector<float> &digits) const = 0;
};

class GenericBBP: public BBP {
 public:
  virtual ~GenericBBP();
  virtual std::string GetDigits(const std::vector<float> &digits) const override;
};

class ParallelBBP: public GenericBBP {
 public:
  ParallelBBP();
  ParallelBBP(std::unique_ptr<OpenCLApplication> ocl_app,
              std::unique_ptr<Logger> logger);
  ~ParallelBBP();

  virtual void Initialize();
  virtual std::vector<float> ComputeDigits(const size_t number_of_digits, const cl_uint starting_position);

  struct Events {
    clpp::Event read_buffer;
    clpp::Event enqueue_nd_range;
  };

  virtual Events GetEvents() const;
 protected:
  virtual clpp::Buffer CreateBuffer(const std::vector<cl_float> output) const;
 private:
  std::unique_ptr<Logger> logger_;

  Events events_;
  std::unique_ptr<OpenCLApplication> ocl_app_;
  clpp::Kernel kernel_;

  const std::string source_file_path_;
  const std::string kernel_name_;
};
};  // parallel
};  // bbp
}  // mila

#endif  // MILA_BBP_PARALLEL_H_
