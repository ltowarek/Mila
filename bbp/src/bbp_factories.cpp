#include "../include/bbp_factories.hpp"

std::unique_ptr<mila::BBP>
mila::BBPFactory::MakeParallel(std::unique_ptr<OpenCLApplication> ocl_app,
                               const std::shared_ptr<Logger> logger) const {
  auto bbp = new mila::ParallelBBP(std::move(ocl_app), logger);
  bbp->Initialize();
  return std::unique_ptr<mila::BBP>(bbp);
}
std::unique_ptr<mila::BBP>
mila::BBPFactory::MakeSequentialBBPProfiler(std::unique_ptr<Profiler> profiler,
                                            const std::shared_ptr<Logger> logger) const {
  auto bbp = std::unique_ptr<mila::SequentialBBP>(new mila::SequentialBBP(logger));
  return std::unique_ptr<mila::BBP>(new mila::SequentialBBPProfiler(std::move(bbp),
                                                                    std::move(profiler),
                                                                    logger));
}
std::unique_ptr<mila::BBP>
mila::BBPFactory::MakeParallelBBPProfiler(std::unique_ptr<OpenCLApplication> ocl_app,
                                          std::unique_ptr<Profiler> profiler,
                                          std::shared_ptr<Logger> logger) const {
  auto bbp = std::unique_ptr<mila::ParallelBBP>(new mila::ParallelBBP(std::move(ocl_app),
                                                                      logger));
  auto bbp_profiler =
      new mila::ParallelBBPProfiler(std::move(bbp), std::move(profiler), logger);
  bbp_profiler->Initialize();
  return std::unique_ptr<mila::BBP>(bbp_profiler);
}
std::unique_ptr<mila::BBP> mila::BBPFactory::MakeSequential(const std::shared_ptr<mila::Logger> logger) const {
  return std::unique_ptr<mila::BBP>(new mila::SequentialBBP(nullptr));
}
