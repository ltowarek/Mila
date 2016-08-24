#ifndef MILA_BBP_PARALLEL_H_
#define MILA_BBP_PARALLEL_H_

#include <string>
#include <vector>
#include <memory>

#include "clpp.h"

#include "bbp_utils.h"
#include "logger.h"
#include "ocl_app.h"
#include "bbp.h"

namespace mila {

class ParallelBBP: public GenericBBP {
 public:
  ParallelBBP();
  ParallelBBP(std::unique_ptr<OpenCLApplication> ocl_app,
              const std::shared_ptr<Logger> logger);
  ~ParallelBBP();

  virtual void Initialize();
  virtual std::vector<float> ComputeDigits(const size_t number_of_digits, const size_t starting_position);

  struct Events {
    clpp::Event read_buffer;
    clpp::Event enqueue_nd_range;
  };

  virtual Events GetEvents() const;
 private:
  clpp::Buffer CreateBuffer(const std::vector<cl_float> output) const;
  const std::shared_ptr<Logger> logger_;

  Events events_;
  const std::unique_ptr<OpenCLApplication> ocl_app_;
  clpp::Kernel kernel_;

  const std::string source_file_path_;
  const std::string kernel_name_;
};
}  // mila

#endif  // MILA_BBP_PARALLEL_H_
