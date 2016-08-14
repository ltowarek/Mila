#include "profiler.h"

mila::Profiler::~Profiler() {

}

mila::ChronoProfiler::~ChronoProfiler() {

}
void mila::ChronoProfiler::Start(const std::string &event_name) {
  durations_[event_name] =
      std::pair<std::chrono::high_resolution_clock::time_point, std::chrono::high_resolution_clock::time_point>();
  durations_[event_name].first = std::chrono::high_resolution_clock::now();
}
void mila::ChronoProfiler::End(const std::string &event_name) {
  durations_[event_name].second = std::chrono::high_resolution_clock::now();
}
std::chrono::duration<long int, std::micro>
mila::ChronoProfiler::GetDuration(const std::string &event_name) const {
  auto duration = std::chrono::microseconds(0);
  if (durations_.count(event_name) > 0) {
    duration = std::chrono::duration_cast<std::chrono::microseconds>(
        durations_.at(event_name).second - durations_.at(event_name).first
    );
  }
  return duration;
}
mila::ChronoProfiler::ChronoProfiler() : ChronoProfiler(nullptr) {

}
mila::ChronoProfiler::ChronoProfiler(std::unique_ptr<mila::Logger> logger)
    : logger_(std::move(logger)) {

}
std::unique_ptr<mila::Profiler>
mila::ProfilerFactory::MakeChrono(std::unique_ptr<mila::Logger> logger) {
  return std::unique_ptr<mila::Profiler>(new mila::ChronoProfiler(std::move(logger)));
}