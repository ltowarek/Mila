#ifndef MILA_BBP_PARALLEL_PROFILER_H_
#define MILA_BBP_PARALLEL_PROFILER_H_

#include <chrono>
#include <map>
#include "bbp_parallel.h"
#include "profiler.h"

namespace mila {

class BBPProfiler: public BBP {
 public:
  virtual ~BBPProfiler() = 0;
};

class BBPProfilerFactory {
 public:
  std::unique_ptr<mila::BBPProfiler> MakeGeneric(std::unique_ptr<mila::BBP> bbp,
                                                 std::unique_ptr<Profiler> profiler,
                                                 const std::shared_ptr<Logger> logger);
  std::unique_ptr<mila::BBPProfiler>
  MakeParallel(std::unique_ptr<OpenCLApplication> ocl_app,
               std::unique_ptr<Profiler> profiler,
               const std::shared_ptr<Logger> logger);
};

class BBPFactory {
 public:
  std::unique_ptr<mila::BBP>
  MakeParallel(std::unique_ptr<OpenCLApplication> ocl_app,
               const std::shared_ptr<Logger> logger);
  std::unique_ptr<mila::BBP>
  MakeGenericBBPProfiler(std::unique_ptr<mila::BBP> bbp,
                         std::unique_ptr<Profiler> profiler,
                         const std::shared_ptr<Logger> logger
  );
  std::unique_ptr<mila::BBP>
  MakeParallelBBPProfiler(std::unique_ptr<OpenCLApplication> ocl_app,
                          std::unique_ptr<Profiler> profiler,
                          const std::shared_ptr<Logger> logger);
};

class GenericBBPProfiler: public BBPProfiler {
 public:
  GenericBBPProfiler();
  GenericBBPProfiler(std::unique_ptr<mila::BBP> bbp,
                     std::unique_ptr<Profiler> profiler,
                     const std::shared_ptr<Logger> logger);
  virtual ~GenericBBPProfiler() override;

  virtual std::vector<float> ComputeDigits(const size_t number_of_digits, const cl_uint starting_position) override;
  virtual std::string GetDigits(const std::vector<float> &digits) const override;
 private:
  const std::unique_ptr<mila::BBP> bbp_;
  const std::unique_ptr<Profiler> profiler_;
  const std::shared_ptr<Logger> logger_;
  size_t number_of_digits_;
};

struct ParallelBBPProfilingResults {
  std::chrono::microseconds compute_digits_duration;
  std::chrono::microseconds initialize_duration;
  std::chrono::microseconds build_kernel_duration;
  std::chrono::microseconds read_buffer_duration;
  std::chrono::microseconds enqueue_nd_range_duration;
  float digits_per_second;
  float bandwidth;
};

class ParallelBBPProfiler: public BBPProfiler {
 public:
  ParallelBBPProfiler();
  ParallelBBPProfiler(std::unique_ptr<mila::ParallelBBP> bbp,
                      std::unique_ptr<Profiler> profiler,
                      const std::shared_ptr<Logger> logger);
  virtual ~ParallelBBPProfiler() override;

  virtual void Initialize();
  virtual std::vector<float> ComputeDigits(const size_t number_of_digits, const cl_uint starting_position) override;
  virtual std::string GetDigits(const std::vector<float> &digits) const override;
  virtual ParallelBBPProfilingResults GetResults() const;
 private:
  const std::unique_ptr<mila::ParallelBBP> bbp_;
  const std::unique_ptr<Profiler> profiler_;
  const std::shared_ptr<Logger> logger_;
  ParallelBBPProfilingResults results_;
  float ComputeBandwidthAsGBPS(size_t number_of_work_items, long microseconds) const;
  std::chrono::duration<long, std::nano> GetProfilingInfo(clpp::Event event) const;
  void SetResultsAfterComputeDigits(const size_t number_of_digits);
  void SetResultsAfterInitialize();
};

}  // mila

#endif  // MILA_BBP_PARALLEL_PROFILER_H_
