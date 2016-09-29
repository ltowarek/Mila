#ifndef MILA_MEAN_SHIFT_FACTORIES_H_
#define MILA_MEAN_SHIFT_FACTORIES_H_

#include <memory>

#include "logger.h"
#include "profiler.h"
#include "ocl_app.h"
#include "mean_shift.h"
#include "mean_shift_image_processing.h"
#include "mean_shift_sequential.h"
#include "mean_shift_sequential_profiler.h"
#include "mean_shift_sequential_app.h"

namespace mila {
class MeanShiftFactory {
 public:
  std::unique_ptr<mila::MeanShift> MakeSequential(const std::shared_ptr<Logger> logger) const;
  std::unique_ptr<mila::MeanShift> MakeSequentialProfiler(std::unique_ptr<Profiler> profiler,
                                                          const std::shared_ptr<Logger> logger) const;
};

class MeanShiftAppFactory {
 public:
  std::unique_ptr<mila::MeanShiftApp> MakeSequential(const std::shared_ptr<Logger> logger) const;
};

class MeanShiftImageProcessingFactory {
 public:
  std::unique_ptr<mila::MeanShiftImageProcessing> MakeSequential(const std::shared_ptr<Logger> logger) const;
  std::unique_ptr<mila::MeanShiftImageProcessing> MakeSequentialProfiler(std::unique_ptr<Profiler> profiler,
                                                                         const std::shared_ptr<Logger> logger) const;
};
}  // mila
#endif  // MILA_MEAN_SHIFT_FACTORIES_H_
