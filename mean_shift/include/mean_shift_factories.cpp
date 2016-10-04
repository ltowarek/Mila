#include "mean_shift_factories.h"

std::unique_ptr<mila::MeanShift> mila::MeanShiftFactory::MakeSequential(const std::shared_ptr<mila::Logger> logger) const {
  return std::unique_ptr<mila::MeanShift>(new mila::SequentialMeanShift(logger));
}
std::unique_ptr<mila::MeanShift>
mila::MeanShiftFactory::MakeSequentialProfiler(std::unique_ptr<Profiler> profiler,
                                               const std::shared_ptr<Logger> logger) const {
  auto mean_shift = std::unique_ptr<mila::SequentialMeanShift>(new mila::SequentialMeanShift(logger));
  return std::unique_ptr<mila::MeanShift>(new mila::SequentialMeanShiftProfiler(std::move(mean_shift),
                                                                                std::move(profiler),
                                                                                logger));
}
std::unique_ptr<mila::MeanShift> mila::MeanShiftFactory::MakeParallel(const std::shared_ptr<mila::Logger> logger) const {
  return std::unique_ptr<mila::MeanShift>(new mila::ParallelMeanShift());
}
std::unique_ptr<mila::MeanShift> mila::MeanShiftFactory::MakeParallelProfiler(std::unique_ptr<mila::Profiler> profiler,
                                                                              const std::shared_ptr<mila::Logger> logger) const {
  return std::unique_ptr<mila::MeanShift>(new mila::ParallelMeanShiftProfiler());
}

std::unique_ptr<mila::MeanShiftImageProcessing> mila::MeanShiftImageProcessingFactory::MakeSequential(
    const std::shared_ptr<mila::Logger> logger) const {
  auto mean_shift = mila::MeanShiftFactory().MakeSequential(logger);
  return std::unique_ptr<mila::MeanShiftImageProcessing>(new mila::MeanShiftImageProcessing(std::move(mean_shift),
                                                                                            logger));
}
std::unique_ptr<mila::MeanShiftImageProcessing>
mila::MeanShiftImageProcessingFactory::MakeSequentialProfiler(std::unique_ptr<Profiler> profiler,
                                                              const std::shared_ptr<Logger> logger) const {
  auto mean_shift = mila::MeanShiftFactory().MakeSequential(logger);
  return std::unique_ptr<mila::MeanShiftImageProcessing>(new mila::MeanShiftImageProcessingProfiler(std::move(mean_shift),
                                                                                                    logger));
}

std::unique_ptr<mila::MeanShiftApp> mila::MeanShiftAppFactory::MakeSequential(const std::shared_ptr<mila::Logger> logger) const {
  return std::unique_ptr<mila::MeanShiftApp>(new mila::SequentialMeanShiftApp(logger));
}
