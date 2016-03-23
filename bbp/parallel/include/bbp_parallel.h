#ifndef MILA_BBP_PARALLEL_H_
#define MILA_BBP_PARALLEL_H_

#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include <CL/cl.h>

namespace mila {
namespace bbp {
namespace parallel {
class BBP {
 public:
  BBP();
  BBP(float precision);
  ~BBP();

  void Initialize();

  float precision() const;
  cl_platform_id platform() const;
  cl_device_id device() const;
  cl_context context() const;
  cl_command_queue queue() const;
  cl_kernel kernel() const;
 private:
  cl_kernel CreateKernel(const std::string& kernel_file, const std::string& kernel_name) const;
  cl_program CreateProgram(const std::string& program_source) const;
  void BuildProgram(const cl_program& program) const;
  std::string ReadFile(const std::string& file) const;
  std::vector<cl_platform_id> GetPlatforms() const;
  std::vector<cl_device_id> GetDevices(const cl_platform_id& platform) const;
  cl_context CreateContext(const cl_platform_id& platform, const std::vector<cl_device_id>& devices) const;
  cl_command_queue CreateQueue(const cl_context& context, const cl_device_id& device) const;

  const float precision_;
  cl_platform_id platform_;
  cl_device_id device_;
  cl_context context_;
  cl_command_queue queue_;
  cl_kernel kernel_;
};
};  // sequential
};  // bbp
}  // mila

#endif  // MILA_BBP_PARALLEL_H_
