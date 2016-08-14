#ifndef MILA_BBP_PARALLEL_PROFILER_H_
#define MILA_BBP_PARALLEL_PROFILER_H_

#include <chrono>
#include <map>
#include "bbp_parallel.h"
#include "statistics.h"

namespace mila {

class BBPProfiler: public BBP {
 public:
  virtual ~BBPProfiler() = 0;
  virtual std::chrono::duration<float, std::micro> ComputeDigitsDuration() const = 0;
  virtual float GetDigitsPerSecond() const = 0;
};

class ProfilerFactory {
 public:
  std::unique_ptr<mila::Profiler> MakeChrono(std::unique_ptr<mila::Logger> logger);
};

class BBPProfilerFactory {
 public:
  std::unique_ptr<mila::BBPProfiler> MakeGeneric(std::unique_ptr<mila::BBP> bbp,
                                                          std::unique_ptr<mila::Profiler> profiler,
                                                          std::unique_ptr<mila::Logger> logger);
  std::unique_ptr<mila::BBPProfiler>
  MakeParallel(std::unique_ptr<mila::OpenCLApplication> ocl_app,
               std::unique_ptr<mila::Profiler> profiler,
               std::unique_ptr<mila::Logger> logger);
};

class BBPFactory {
 public:
  std::unique_ptr<mila::BBP>
  MakeParallel(std::unique_ptr<mila::OpenCLApplication> ocl_app,
               std::unique_ptr<mila::Logger> logger);
  std::unique_ptr<mila::BBP>
  MakeGenericBBPProfiler(std::unique_ptr<mila::BBP> bbp,
                         std::unique_ptr<mila::Profiler> profiler,
                         std::unique_ptr<mila::Logger> logger
  );
  std::unique_ptr<mila::BBP>
  MakeParallelBBPProfiler(std::unique_ptr<mila::OpenCLApplication> ocl_app,
                          std::unique_ptr<mila::Profiler> profiler,
                          std::unique_ptr<mila::Logger> logger);
};

template<typename F, typename... A>
std::chrono::duration<float> ProfileFunction(F &&f, A &&... a) {
  auto start_time = std::chrono::high_resolution_clock::now();
  f(std::forward<A>(a)...);
  auto end_time = std::chrono::high_resolution_clock::now();
  return std::chrono::duration<float>(end_time - start_time);
};

class OpenCLApplicationProfiler: public OpenCLApplication {
 public:
  OpenCLApplicationProfiler();
  OpenCLApplicationProfiler(std::unique_ptr<OpenCLApplication> app);
  virtual void Initialize() override;
  virtual clpp::Program CreateProgramFromSource(const std::string &source_file_path) const override;
  virtual void BuildProgram(const clpp::Program &program, const clpp::Device &device) const override;
  virtual clpp::Kernel CreateKernel(const std::string &kernel_name, const std::string &source_file_path) override;
  virtual clpp::Platform GetPlatform() const override;
  virtual std::string GetPlatformName() const override;
  virtual clpp::Device GetDevice() const override;
  virtual std::string GetDeviceName() const override;
  virtual clpp::Context GetContext() const override;
  virtual clpp::Queue GetQueue() const override;
 private:
  std::unique_ptr<OpenCLApplication> app_;
};

class GenericBBPProfiler: public BBPProfiler{
 public:
  GenericBBPProfiler();
  GenericBBPProfiler(std::unique_ptr<mila::BBP> bbp,
                     std::unique_ptr<mila::Profiler> profiler,
                     std::unique_ptr<mila::Logger> logger);
  virtual ~GenericBBPProfiler() override;

  virtual std::vector<float> ComputeDigits(const size_t number_of_digits, const cl_uint starting_position) override;
  virtual std::string GetDigits(const std::vector<float> &digits) const override;
  virtual std::chrono::duration<float, std::micro> ComputeDigitsDuration() const override;
  virtual float GetDigitsPerSecond() const override;
 private:
  const std::unique_ptr<mila::BBP> bbp_;
  const std::unique_ptr<mila::Profiler> profiler_;
  const std::unique_ptr<mila::Logger> logger_;
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
                      std::unique_ptr<Logger> logger);
  virtual ~ParallelBBPProfiler() override;

  virtual void Initialize();
  virtual std::vector<float> ComputeDigits(const size_t number_of_digits, const cl_uint starting_position) override;
  virtual std::string GetDigits(const std::vector<float> &digits) const override;
  virtual std::chrono::duration<float, std::micro> ComputeDigitsDuration() const override;
  virtual std::chrono::duration<float, std::micro> InitializeDuration() const;
  virtual float GetDigitsPerSecond() const override;
  virtual ParallelBBPProfilingResults GetResults() const;
 private:
  const std::unique_ptr<mila::ParallelBBP> bbp_;
  const std::unique_ptr<mila::Profiler> profiler_;
  const std::unique_ptr<mila::Logger> logger_;
  size_t number_of_digits_;
  ParallelBBPProfilingResults results_;
  float ComputeBandwidthAsGBPS(size_t number_of_work_items, long microseconds) const;
  std::chrono::duration<long, std::nano> GetProfilingInfo(clpp::Event event) const;
  void SetResultsAfterComputeDigits(const size_t number_of_digits);
  void SetResultsAfterInitialize();
};

}  // mila

#endif  // MILA_BBP_PARALLEL_PROFILER_H_
