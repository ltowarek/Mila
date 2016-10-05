#ifndef MILA_MEAN_SHIFT_PARALLEL_H_
#define MILA_MEAN_SHIFT_PARALLEL_H_

#include <cstddef>

#include "clpp.h"
#include "mean_shift.h"
#include "mean_shift_utils.h"
#include "ocl_app.h"
#include "utils.h"

namespace mila {
class ParallelMeanShift : public MeanShift {
 public:
  ParallelMeanShift(std::unique_ptr<OpenCLApplication> ocl_app,
                    const std::shared_ptr<Logger> logger);
  virtual ~ParallelMeanShift() override;

  virtual void Initialize();
  virtual std::vector<Point> Run(const std::vector<Point> &points, const float bandwidth) override;
 protected:
  void UpdateEvents(clpp::Event copy_buffer, clpp::Event read_buffer, clpp::Event enqueue_nd_range);

  struct Events {
    std::vector<clpp::Event> copy_buffer;
    std::vector<clpp::Event> read_buffer_with_distances;
    std::vector<clpp::Event> enqueue_nd_range;
    clpp::Event read_buffer_with_output;
  };

  const std::shared_ptr<Logger> logger_;
  const std::unique_ptr<OpenCLApplication> ocl_app_;

  Events events_;
  clpp::Kernel kernel_;
};

}  // mila
#endif  // MILA_MEAN_SHIFT_PARALLEL_H_
