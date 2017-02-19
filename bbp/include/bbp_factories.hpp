#ifndef MILA_BBP_FACTORIES_HPP
#define MILA_BBP_FACTORIES_HPP

#include <memory>

#include "logger.hpp"
#include "profiler.hpp"
#include "ocl_app.hpp"
#include "bbp.hpp"
#include "bbp_parallel_profiler.hpp"
#include "bbp_parallel_app.hpp"
#include "bbp_sequential_profiler.hpp"
#include "bbp_sequential_app.hpp"

namespace mila {
class BBPFactory {
 public:
  std::unique_ptr<mila::BBP>
  MakeParallel(std::unique_ptr<OpenCLApplication> ocl_app,
               const std::shared_ptr<Logger> logger) const;
  std::unique_ptr<mila::BBP>
  MakeParallelBBPProfiler(std::unique_ptr<OpenCLApplication> ocl_app,
                          std::unique_ptr<Profiler> profiler,
                          const std::shared_ptr<Logger> logger) const;
  std::unique_ptr<mila::BBP> MakeSequential(const std::shared_ptr<Logger> logger) const;
  std::unique_ptr<mila::BBP> MakeSequentialBBPProfiler(std::unique_ptr<Profiler> profiler,
                                                       const std::shared_ptr<Logger> logger) const;
};
}  // mila
#endif  // MILA_BBP_FACTORIES_HPP
