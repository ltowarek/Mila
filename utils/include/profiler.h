#ifndef MILA_PROFILER_H
#define MILA_PROFILER_H

#include <chrono>
#include <map>
#include <memory>
#include <string>

#include "logger.h"

namespace mila {
class Profiler {
 public:
  virtual ~Profiler() = 0;
  virtual void Start(const std::string &event_name) = 0;
  virtual void End(const std::string &event_name) = 0;
  virtual std::chrono::duration<long int, std::micro> GetDuration(
      const std::string &event_name
  ) const = 0;
};
class ChronoProfiler: public Profiler {
 public:
  ChronoProfiler();
  explicit ChronoProfiler(std::unique_ptr<mila::Logger> logger);
  virtual ~ChronoProfiler() override;
  virtual void Start(const std::string &event_name) override;
  virtual void End(const std::string &event_name) override;
  virtual std::chrono::duration<long int, std::micro> GetDuration(
      const std::string &event_name
  )
  const override;
 private:
  std::unique_ptr<mila::Logger> logger_;
  std::map<std::string,
           std::pair<std::chrono::high_resolution_clock::time_point, std::chrono::high_resolution_clock::time_point>>
      durations_;
};
class ProfilerFactory {
 public:
  std::unique_ptr<mila::Profiler> MakeChrono(std::unique_ptr<mila::Logger> logger);
};
}  // mila
#endif //MILA_PROFILER_H
