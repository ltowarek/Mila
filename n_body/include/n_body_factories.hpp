#ifndef MILA_N_BODY_FACTORIES_HPP
#define MILA_N_BODY_FACTORIES_HPP

#include <memory>

#include "logger.hpp"
#include "profiler.hpp"
#include "ocl_app.hpp"
#include "n_body.hpp"
#include "n_body_sequential.hpp"
#include "n_body_sequential_profiler.hpp"
#include "n_body_sequential_app.hpp"
#include "n_body_parallel.hpp"
#include "n_body_parallel_profiler.hpp"
#include "n_body_parallel_app.hpp"
#include "n_body_interactive_view_app.hpp"

namespace mila {
class NBodyFactory {
 public:
  std::unique_ptr<mila::NBody> MakeSequential(const std::shared_ptr<Logger> logger) const;
  std::unique_ptr<mila::NBody> MakeSequentialProfiler(std::unique_ptr<Profiler> profiler,
                                                      const std::shared_ptr<Logger> logger) const;
  std::unique_ptr<mila::NBody> MakeParallel(std::unique_ptr<OpenCLApplication> ocl_app,
                                            const std::shared_ptr<Logger> logger) const;
  std::unique_ptr<mila::NBody> MakeParallelProfiler(std::unique_ptr<OpenCLApplication> ocl_app,
                                                    std::unique_ptr<Profiler> profiler,
                                                    const std::shared_ptr<Logger> logger) const;
};
}  // mila
#endif  // MILA_N_BODY_FACTORIES_HPP
