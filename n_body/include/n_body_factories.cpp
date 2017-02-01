#include "n_body_factories.h"

std::unique_ptr<mila::NBody> mila::NBodyFactory::MakeSequential(const std::shared_ptr<mila::Logger> logger) const {
  return std::unique_ptr<mila::NBody>(new mila::SequentialNBody(logger));
}

std::unique_ptr<mila::NBody>
mila::NBodyFactory::MakeSequentialProfiler(std::unique_ptr<Profiler> profiler,
                                           const std::shared_ptr<Logger> logger) const {
  auto n_body = std::unique_ptr<mila::SequentialNBody>(new mila::SequentialNBody(logger));
  return std::unique_ptr<mila::NBody>(new mila::SequentialNBodyProfiler(std::move(n_body),
                                                                        std::move(profiler),
                                                                        logger));
}

std::unique_ptr<mila::NBody> mila::NBodyFactory::MakeParallel(std::unique_ptr<OpenCLApplication> ocl_app,
                                                              const std::shared_ptr<Logger> logger) const {
  auto n_body = new mila::ParallelNBody(std::move(ocl_app), logger);
  n_body->Initialize();
  return std::unique_ptr<mila::NBody>(n_body);
}

std::unique_ptr<mila::NBody> mila::NBodyFactory::MakeParallelProfiler(std::unique_ptr<OpenCLApplication> ocl_app,
                                                                      std::unique_ptr<mila::Profiler> profiler,
                                                                      const std::shared_ptr<mila::Logger> logger) const {
  auto n_body = std::unique_ptr<mila::ParallelNBody>(new mila::ParallelNBody(std::move(ocl_app),
                                                                             logger));
  auto n_body_profiler =
      new mila::ParallelNBodyProfiler(std::move(n_body), std::move(profiler), logger);
  n_body_profiler->Initialize();
  return std::unique_ptr<mila::NBody>(n_body_profiler);
}

std::unique_ptr<mila::NBodyApp> mila::NBodyAppFactory::MakeSequential(const std::shared_ptr<mila::Logger> logger) const {
  return std::unique_ptr<mila::NBodyApp>(new mila::SequentialNBodyApp(logger));
}

std::unique_ptr<mila::NBodyApp> mila::NBodyAppFactory::MakeParallel(const std::shared_ptr<mila::Logger> logger) const {
  return std::unique_ptr<mila::NBodyApp>(new mila::ParallelNBodyApp(logger));
}
