#ifndef MILA_MEAN_SHIFT_PARALLEL_H_
#define MILA_MEAN_SHIFT_PARALLEL_H_

#include <cstddef>

#include "clpp.h"
#include "mean_shift.h"
#include "mean_shift_utils.h"
#include "utils.h"

namespace mila {
class ParallelMeanShift : public MeanShift {
 public:
  ParallelMeanShift();
  ParallelMeanShift(size_t platform_id, size_t device_id);
  ParallelMeanShift(size_t platform_id, size_t device_id, float precision, size_t max_iterations);
  virtual ~ParallelMeanShift() override;

  virtual void Initialize();
  virtual std::vector<Point> Run(const std::vector<Point> &points, const float bandwidth) override;
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

}  // mila
#endif  // MILA_MEAN_SHIFT_PARALLEL_H_
