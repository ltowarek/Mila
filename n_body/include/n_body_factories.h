#ifndef MILA_N_BODY_FACTORIES_H_
#define MILA_N_BODY_FACTORIES_H_

#include <memory>

#include "logger.h"
#include "profiler.h"
#include "ocl_app.h"
#include "n_body.h"
#include "n_body_sequential.h"
#include "n_body_sequential_profiler.h"
#include "n_body_sequential_app.h"
#include "n_body_parallel.h"
#include "n_body_parallel_profiler.h"
#include "n_body_parallel_app.h"
#include "n_body_interactive_view_app.h"

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
#endif  // MILA_N_BODY_FACTORIES_H_
