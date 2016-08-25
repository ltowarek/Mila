#ifndef MILA_BBP_FACTORIES_H_
#define MILA_BBP_FACTORIES_H_

#include <memory>

#include "logger.h"
#include "profiler.h"
#include "ocl_app.h"
#include "bbp.h"
#include "bbp_parallel_profiler.h"
#include "bbp_parallel_app.h"

namespace mila {
class BBPFactory {
 public:
  std::unique_ptr<mila::BBP>
  MakeParallel(std::unique_ptr<OpenCLApplication> ocl_app,
               const std::shared_ptr<Logger> logger) const;
  std::unique_ptr<mila::BBP>
  MakeGenericBBPProfiler(std::unique_ptr<mila::BBP> bbp,
                         std::unique_ptr<Profiler> profiler,
                         const std::shared_ptr<Logger> logger
  ) const;
  std::unique_ptr<mila::BBP>
  MakeParallelBBPProfiler(std::unique_ptr<OpenCLApplication> ocl_app,
                          std::unique_ptr<Profiler> profiler,
                          const std::shared_ptr<Logger> logger) const;
};

class BBPAppFactory {
 public:
  std::unique_ptr<mila::BBPApp> MakeParallel(const std::shared_ptr<Logger> logger) const;
};

}  // mila

#endif  // MILA_BBP_FACTORIES_H_
