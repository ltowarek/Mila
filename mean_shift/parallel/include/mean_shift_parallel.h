#ifndef MILA_MEAN_SHIFT_PARALLEL_H_
#define MILA_MEAN_SHIFT_PARALLEL_H_

#include <cstddef>

#include "clpp.h"
#include "mean_shift_utils.h"
#include "utils.h"

namespace mila {
namespace meanshift {
namespace parallel {

std::vector<cl_float4> ConvertVectorToPoints(const std::vector<uint8_t> &data);
std::vector<uint8_t> ConvertPointsToVector(const std::vector<cl_float4> &data);

class MeanShift {
 public:
  MeanShift();
  MeanShift(size_t platform_id, size_t device_id);
  MeanShift(size_t platform_id, size_t device_id, float precision, size_t max_iterations);

  virtual void Initialize();
  virtual std::vector<cl_float4> Run(const std::vector<cl_float4> &points, float bandwidth);

  float precision() const;
  size_t max_iterations() const;
  size_t platform_id() const;
  size_t device_id() const;
  clpp::Platform platform() const;
  clpp::Device device() const;
  clpp::Context context() const;
  clpp::Queue queue() const;
  clpp::Kernel kernel() const;
 protected:
  virtual void BuildProgram(const clpp::Program& program, const clpp::Device& device);
  void UpdateEvents(clpp::Event copy_buffer, clpp::Event read_buffer, clpp::Event enqueue_nd_range);

  struct Events {
    std::vector<clpp::Event> copy_buffer;
    std::vector<clpp::Event> read_buffer_with_distances;
    std::vector<clpp::Event> enqueue_nd_range;
    clpp::Event read_buffer_with_output;
  };

  Events events_;
  const float precision_;
  const size_t max_iterations_;
  const size_t platform_id_;
  const size_t device_id_;
  clpp::Platform platform_;
  clpp::Device device_;
  clpp::Context context_;
  clpp::Queue queue_;
  clpp::Kernel kernel_;
};

class MeanShiftImageProcessing: public MeanShift {
 public:
  MeanShiftImageProcessing();
  MeanShiftImageProcessing(size_t platform_id, size_t device_id);
  MeanShiftImageProcessing(size_t platform_id, size_t device_id, float precision, size_t max_iterations);

  virtual std::vector<cl_float4> Run(const std::vector<cl_float4> &points, float bandwidth) override;
  virtual void Run(const std::string &input_file, const std::string &output_file, float bandwidth);
};

}  // parallel
}  // meanshift
}  // mila

#endif  // MILA_MEAN_SHIFT_PARALLEL_H_
