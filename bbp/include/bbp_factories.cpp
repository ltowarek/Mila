#include "bbp_factories.h"

std::unique_ptr<mila::BBP>
mila::BBPFactory::MakeParallel(std::unique_ptr<OpenCLApplication> ocl_app,
                               const std::shared_ptr<Logger> logger) {
  auto bbp = new mila::ParallelBBP(std::move(ocl_app), logger);
  bbp->Initialize();
  return std::unique_ptr<mila::BBP>(bbp);
}
std::unique_ptr<mila::BBP>
mila::BBPFactory::MakeGenericBBPProfiler(std::unique_ptr<mila::BBP> bbp,
                                         std::unique_ptr<Profiler> profiler,
                                         const std::shared_ptr<Logger> logger) {
  return std::unique_ptr<mila::BBP>(new mila::GenericBBPProfiler(std::move(bbp),
                                                                 std::move(profiler),
                                                                 logger));
}
std::unique_ptr<mila::BBP>
mila::BBPFactory::MakeParallelBBPProfiler(std::unique_ptr<OpenCLApplication> ocl_app,
                                          std::unique_ptr<Profiler> profiler,
                                          std::shared_ptr<Logger> logger) {
  auto bbp = std::unique_ptr<mila::ParallelBBP>(new mila::ParallelBBP(std::move(ocl_app),
                                                                      logger));
  auto bbp_profiler =
      new mila::ParallelBBPProfiler(std::move(bbp), std::move(profiler), logger);
  bbp_profiler->Initialize();
  return std::unique_ptr<mila::BBP>(bbp_profiler);
}
