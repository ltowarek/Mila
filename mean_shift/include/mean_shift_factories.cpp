#include "mean_shift_factories.h"

std::unique_ptr<mila::MeanShift> mila::MeanShiftFactory::MakeSequential(const std::shared_ptr<mila::Logger> logger) const {
  return std::unique_ptr<mila::MeanShift>(new mila::SequentialMeanShift(logger));
}
std::unique_ptr<mila::MeanShift>
mila::MeanShiftFactory::MakeSequentialMeanShiftProfiler(std::unique_ptr<Profiler> profiler,
                                                        const std::shared_ptr<Logger> logger) const {
  auto mean_shift = std::unique_ptr<mila::SequentialMeanShift>(new mila::SequentialMeanShift(logger));
  return std::unique_ptr<mila::MeanShift>(new mila::SequentialMeanShiftProfiler());
}
