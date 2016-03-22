#ifndef MILA_BBP_PARALLEL_H_
#define MILA_BBP_PARALLEL_H_

#include <CL/cl.h>

namespace mila {
namespace bbp {
namespace parallel {
class BBP {
 public:
  BBP();
  BBP(float precision);
  BBP(cl_platform_id platform, cl_device_id device, cl_context context, cl_command_queue queue, float precision);

  void Initialize();

  float precision() const;
  cl_platform_id platform() const;
  cl_device_id device() const;
  cl_context context() const;
  cl_command_queue queue() const;
 private:
  const float precision_;
  cl_platform_id platform_;
  cl_device_id device_;
  cl_context context_;
  cl_command_queue queue_;
};
};  // sequential
};  // bbp
}  // mila

#endif  // MILA_BBP_PARALLEL_H_
