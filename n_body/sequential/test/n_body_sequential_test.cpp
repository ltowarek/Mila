#include "gtest/gtest.h"
#include "n_body_sequential.hpp"
#include "n_body_sequential_profiler.hpp"
#include "n_body_sequential_app.hpp"

TEST(SequentialNBodyTest, ApplyCentralForceZeroDistance) {
  const auto n_body = mila::SequentialNBody(nullptr);
  auto particle = mila::Particle{0.0f};
  particle.acceleration = {2.0f, 2.0f};
  const auto center = mila::Vector2D{0.0f, 0.0f};

  n_body.ApplyCentralForce(center, 3.0f, particle);

  EXPECT_EQ(particle.acceleration.x, 2.0f);
  EXPECT_EQ(particle.acceleration.y, 2.0f);
}

TEST(SequentialNBodyTest, ApplyCentralForceZeroForce) {
  const auto n_body = mila::SequentialNBody(nullptr);
  auto particle = mila::Particle{0.0f};
  particle.position = {1.0f, 1.0f};
  particle.acceleration = {2.0f, 2.0f};
  const auto center = mila::Vector2D{0.0f, 0.0f};

  n_body.ApplyCentralForce(center, 0.0f, particle);

  EXPECT_EQ(particle.acceleration.x, 2.0f);
  EXPECT_EQ(particle.acceleration.y, 2.0f);
}

TEST(SequentialNBodyTest, ApplyCentralForceSimple) {
  const auto n_body = mila::SequentialNBody(nullptr);
  auto particle = mila::Particle{0.0f};
  particle.position = {1.0f, 1.0f};
  const auto center = mila::Vector2D{0.0f, 0.0f};

  n_body.ApplyCentralForce(center, 2.0f, particle);

  EXPECT_EQ(particle.acceleration.x, -2.0f);
  EXPECT_EQ(particle.acceleration.y, -2.0f);
}

TEST(SequentialNBodyTest, ApplyCentralForceComplex) {
  const auto n_body = mila::SequentialNBody(nullptr);
  auto particle = mila::Particle{0.0f};
  particle.position = {1.0f, 1.0f};
  particle.acceleration = {2.0f, 2.0f};
  const auto center = mila::Vector2D{0.0f, 0.0f};

  n_body.ApplyCentralForce(center, 3.0f, particle);

  EXPECT_EQ(particle.acceleration.x, -1.0f);
  EXPECT_EQ(particle.acceleration.y, -1.0f);
}

TEST(SequentialNBodyTest, ApplyDampingForceZeroVelocity) {
  const auto n_body = mila::SequentialNBody(nullptr);
  auto particle = mila::Particle{0.0f};

  n_body.ApplyDampingForce(1.0f, particle);

  EXPECT_EQ(particle.velocity.x, 0.0f);
  EXPECT_EQ(particle.velocity.y, 0.0f);
}

TEST(SequentialNBodyTest, ApplyDampingForceZeroForce) {
  const auto n_body = mila::SequentialNBody(nullptr);
  auto particle = mila::Particle{0.0f};
  particle.velocity = {1.0f, 1.0f};

  n_body.ApplyDampingForce(0.0f, particle);

  EXPECT_EQ(particle.velocity.x, 0.0f);
  EXPECT_EQ(particle.velocity.y, 0.0f);
}

TEST(SequentialNBodyTest, ApplyDampingForceSimple) {
  const auto n_body = mila::SequentialNBody(nullptr);
  auto particle = mila::Particle{0.0f};
  particle.velocity = {1.0f, 1.0f};

  n_body.ApplyDampingForce(1.0f, particle);

  EXPECT_EQ(particle.velocity.x, 1.0f);
  EXPECT_EQ(particle.velocity.y, 1.0f);
}

TEST(SequentialNBodyTest, ApplyDampingForceComplex) {
  const auto n_body = mila::SequentialNBody(nullptr);
  auto particle = mila::Particle{0.0f};
  particle.velocity = {2.0f, 3.0f};

  n_body.ApplyDampingForce(4.0f, particle);

  EXPECT_EQ(particle.velocity.x, 8.0f);
  EXPECT_EQ(particle.velocity.y, 12.0f);
}

TEST(SequentialNBodyTest, ApplyMotionWithoutAcceleration) {
  const auto n_body = mila::SequentialNBody(nullptr);
  auto particle = mila::Particle{0.0f};
  particle.position = {1.0f, 1.0f};
  particle.velocity = {1.0f, 1.0f};

  n_body.ApplyMotion(particle);

  EXPECT_EQ(particle.position.x, 2.0f);
  EXPECT_EQ(particle.position.y, 2.0f);
  EXPECT_EQ(particle.velocity.x, 1.0f);
  EXPECT_EQ(particle.velocity.y, 1.0f);
  EXPECT_EQ(particle.acceleration.x, 0.0f);
  EXPECT_EQ(particle.acceleration.y, 0.0f);
}

TEST(SequentialNBodyTest, ApplyMotionWithAcceleration) {
  const auto n_body = mila::SequentialNBody(nullptr);
  auto particle = mila::Particle{0.0f};
  particle.position = {1.0f, 1.0f};
  particle.velocity = {1.0f, 1.0f};
  particle.acceleration = {2.0f, 2.0f};

  n_body.ApplyMotion(particle);

  EXPECT_EQ(particle.position.x, 4.0f);
  EXPECT_EQ(particle.position.y, 4.0f);
  EXPECT_EQ(particle.velocity.x, 3.0f);
  EXPECT_EQ(particle.velocity.y, 3.0f);
  EXPECT_EQ(particle.acceleration.x, 0.0f);
  EXPECT_EQ(particle.acceleration.y, 0.0f);
}

TEST(SequentialNBodyProfilerTest, GetResultsAfterUpdateParticles) {
  auto n_body = std::unique_ptr<mila::SequentialNBody>(new mila::SequentialNBody(nullptr));
  auto profiler = std::unique_ptr<mila::Profiler>(new mila::ProfilerStub());
  auto n_body_profiler = mila::SequentialNBodyProfiler(std::move(n_body), std::move(profiler), nullptr);
  auto particles = std::vector<mila::Particle>{
      {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}},
      {{10.0f, 20.0f}, {30.0f, 40.0f}, {50.0f, 60.0f}}
  };
  const mila::NBodyParameters parameters{};

  n_body_profiler.UpdateParticles(parameters, mila::Vector2D{1.0f, 1.0f}, particles);

  EXPECT_GT(n_body_profiler.GetResults().update_particles_duration.count(), 0);
  EXPECT_GT(n_body_profiler.GetResults().particles_per_second, 0.0f);
}

TEST(SequentialNBodyAppTest, Run) {
  const auto logger_spy = std::shared_ptr<mila::LoggerSpy>(new mila::LoggerSpy());
  const auto number_of_particles = std::string("100");
  const auto number_of_iterations = std::string("10");
  const char *parameters[] = {"app", number_of_particles.c_str(), number_of_iterations.c_str()};
  const auto n_body = mila::SequentialNBodyApp(logger_spy);
  // const_cast due to C vs C++ string literals
  n_body.Run(3, const_cast<char **>(parameters));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of particles: " + number_of_particles));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of iterations: " + number_of_iterations));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Update particles duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Update particles duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Update particles duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Update particles duration coefficient of variation: "));
}
