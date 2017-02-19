#ifndef MILA_MEAN_SHIFT_FACTORIES_HPP
#define MILA_MEAN_SHIFT_FACTORIES_HPP

#include <memory>

#include "logger.hpp"
#include "profiler.hpp"
#include "ocl_app.hpp"
#include "mean_shift.hpp"
#include "mean_shift_image_processing.hpp"
#include "mean_shift_image_processing_profiler.hpp"
#include "mean_shift_image_processing_app.hpp"
#include "mean_shift_sequential.hpp"
#include "mean_shift_sequential_profiler.hpp"
#include "mean_shift_sequential_app.hpp"
#include "mean_shift_parallel.hpp"
#include "mean_shift_parallel_profiler.hpp"
#include "mean_shift_parallel_app.hpp"

namespace mila {
class MeanShiftFactory {
 public:
  std::unique_ptr<mila::MeanShift> MakeSequential(const std::shared_ptr<Logger> logger) const;
  std::unique_ptr<mila::MeanShift> MakeSequentialProfiler(std::unique_ptr<Profiler> profiler,
                                                          const std::shared_ptr<Logger> logger) const;
  std::unique_ptr<mila::MeanShift> MakeParallel(std::unique_ptr<OpenCLApplication> ocl_app, const std::shared_ptr<Logger> logger) const;
  std::unique_ptr<mila::MeanShift> MakeParallelProfiler(std::unique_ptr<OpenCLApplication> ocl_app,
                                                        std::unique_ptr<Profiler> profiler,
                                                        const std::shared_ptr<Logger> logger) const;
};

class MeanShiftImageProcessingFactory {
 public:
  std::unique_ptr<mila::MeanShiftImageProcessing> MakeSequential(const std::shared_ptr<Logger> logger) const;
  std::unique_ptr<mila::MeanShiftImageProcessing> MakeSequentialProfiler(std::unique_ptr<Profiler> profiler,
                                                                         const std::shared_ptr<Logger> logger) const;
};
}  // mila
#endif  // MILA_MEAN_SHIFT_FACTORIES_HPP
