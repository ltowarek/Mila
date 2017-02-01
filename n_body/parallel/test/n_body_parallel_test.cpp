#include "gtest/gtest.h"
#include "n_body_parallel.h"
#include "n_body_parallel_profiler.h"
#include "n_body_parallel_app.h"

class ParallelNBodyProfilerTest : public testing::Test {
 protected:
  virtual void SetUp() {
    auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, nullptr);
    auto profiler = std::unique_ptr<mila::Profiler>(new mila::ProfilerStub());
    auto n_body = std::unique_ptr<mila::ParallelNBody>(new mila::ParallelNBody(std::move(ocl_app),
                                                                               nullptr));
    auto n_body_profiler = new mila::ParallelNBodyProfiler(std::move(n_body), std::move(profiler), nullptr);
    n_body_ = std::unique_ptr<mila::ParallelNBodyProfiler>(n_body_profiler);
  }
  std::unique_ptr<mila::ParallelNBodyProfiler> n_body_;
};

TEST_F(ParallelNBodyProfilerTest, GetResultsAfterInitialize) {
  this->n_body_->Initialize();
  EXPECT_GT(this->n_body_->GetResults().initialize_duration.count(), 0);
}

TEST_F(ParallelNBodyProfilerTest, GetResultsAfterRun) {
  auto particles = std::vector<mila::Particle>{
      {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}},
      {{10.0f, 20.0f}, {30.0f, 40.0f}, {50.0f, 60.0f}}
  };
  const mila::NBodyParameters parameters{};

  this->n_body_->Initialize();
  this->n_body_->UpdateParticles(parameters, mila::Vector2D{1.0f, 1.0f}, particles);
  EXPECT_GT(this->n_body_->GetResults().update_particles_duration.count(), 0);
  EXPECT_GT(this->n_body_->GetResults().initialize_duration.count(), 0);
  EXPECT_GT(this->n_body_->GetResults().enqueue_nd_range_duration.count(), 0);
  EXPECT_GT(this->n_body_->GetResults().read_buffer_duration.count(), 0);
  EXPECT_GT(this->n_body_->GetResults().particles_per_second, 0.0f);
  EXPECT_GT(this->n_body_->GetResults().bandwidth, 0.0f);
}

TEST(ParallelNBodyAppTest, Run) {
  const auto logger_spy = std::shared_ptr<mila::LoggerSpy>(new mila::LoggerSpy());
  const auto number_of_particles = std::string("100");
  const auto platform_id = std::string("0");
  const auto device_id = std::string("0");
  const auto number_of_iterations = std::string("10");
  const char *parameters[] =
      {"app", number_of_particles.c_str(), platform_id.c_str(), device_id.c_str(), number_of_iterations.c_str()};
  const auto n_body = mila::ParallelNBodyApp(logger_spy);
  // const_cast due to C vs C++ string literals
  n_body.Run(5, const_cast<char **>(parameters));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of particles: " + number_of_particles));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of iterations: " + number_of_iterations));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Platform id: " + platform_id));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Device id: " + device_id));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Bandwidth mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Bandwidth median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Bandwidth standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Bandwidth coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Initialize duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Initialize duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Initialize duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Initialize duration coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Update particles duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Update particles duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Update particles duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Update particles duration coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Enqueue ND range duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Enqueue ND range duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Enqueue ND range duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Enqueue ND range duration coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Read buffer duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Read buffer duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Read buffer duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Read buffer duration coefficient of variation: "));
}
