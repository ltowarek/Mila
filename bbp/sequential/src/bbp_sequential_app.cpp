#include "bbp_sequential_app.hpp"

mila::SequentialBBPApp::SequentialBBPApp(const std::shared_ptr<mila::Logger> logger): logger_(logger) {

}
mila::SequentialBBPApp::~SequentialBBPApp() {

}
void mila::SequentialBBPApp::Run(int argc, char **argv) const {
  auto config = ParseCommandLine(argc, argv);
  PrintParameters(config);
  auto raw_results = RunIterations(config);
  auto prepared_results = PrepareResults(raw_results);
  PrintResultsStatistics(prepared_results);
}
mila::SequentialBBPApp::Parameters mila::SequentialBBPApp::ParseCommandLine(int argc, char **argv) const {
  if (argc < 4) {
    throw std::runtime_error("Wrong number of parameters: " + std::to_string(argc));
  }
  auto config = Parameters{0};
  config.number_of_digits = static_cast<size_t>(atoi(argv[1]));
  config.starting_position = static_cast<size_t>(atoi(argv[2]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[3]));
  return config;
}
std::vector<mila::SequentialBBPProfilingResults> mila::SequentialBBPApp::RunIterations(const mila::SequentialBBPApp::Parameters config) const {
  auto results = std::vector<mila::SequentialBBPProfilingResults>();
  const auto warm_up_iterations = 1;
  for (size_t i = 0; i < config.number_of_iterations + warm_up_iterations; ++i) {
    logger_->Debug("Iteration: %d", i);

    auto bbp = std::unique_ptr<mila::SequentialBBP>(new mila::SequentialBBP(logger_));
    auto profiler = mila::ProfilerFactory().MakeChrono(logger_);
    auto bbp_profiler = std::unique_ptr<mila::SequentialBBPProfiler>(new mila::SequentialBBPProfiler(std::move(bbp), std::move(profiler), logger_));
    auto digits = bbp_profiler->ComputeDigits(config.number_of_digits, config.starting_position);
    auto digits_str = bbp_profiler->GetDigits(digits);

    if (i == 0) {
      logger_->Info("Digits: %s", digits_str.c_str());
    } else {
      logger_->Debug("Digits: %s", digits_str.c_str());
    }

    PrintResults(bbp_profiler->GetResults());

    if (i >= warm_up_iterations) {
      results.push_back(bbp_profiler->GetResults());
    }
  }
  return results;
}
mila::SequentialBBPApp::Results mila::SequentialBBPApp::PrepareResults(const std::vector<mila::SequentialBBPProfilingResults> &raw_results) const {
  auto prepared_results = Results{};
  for (const auto& result : raw_results) {
    prepared_results.digits_per_second.push_back(result.digits_per_second);
    prepared_results.compute_digits_duration.push_back(result.compute_digits_duration.count());
  }
  return prepared_results;
}
void mila::SequentialBBPApp::PrintParameters(const mila::SequentialBBPApp::Parameters &config) const {
  logger_->Info("Number of digits: %d", config.number_of_digits);
  logger_->Info("Starting position: %d", config.starting_position);
  logger_->Info("Number of iterations: %d", config.number_of_iterations);
}
void mila::SequentialBBPApp::PrintResults(const mila::SequentialBBPProfilingResults &results) const {
  logger_->Debug("Throughput: %f digits/s", results.digits_per_second);
  logger_->Debug("Compute digits duration: %llu us", results.compute_digits_duration);
}
void mila::SequentialBBPApp::PrintResultsStatistics(const mila::SequentialBBPApp::Results &results) const {
  mila::PrintResultStatistics("Throughput", "digits/s", results.digits_per_second, *logger_);
  mila::PrintResultStatistics("Compute digits duration", "us", results.compute_digits_duration, *logger_);
}
