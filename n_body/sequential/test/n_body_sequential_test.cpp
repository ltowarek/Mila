#include "gtest/gtest.h"
#include "n_body_sequential.h"
#include "n_body_sequential_profiler.h"
#include "n_body_sequential_app.h"

TEST(NBodySequentialTest, ApplyCentralForceZeroDistance) {
  mila::SequentialNBody n_body(nullptr);
  mila::Particle particle{0.0f};
  particle.acceleration = {2.0f, 2.0f};
  mila::Vector2D center{0.0f, 0.0f};

  n_body.ApplyCentralForce(center, 3.0f, particle);

  EXPECT_EQ(particle.acceleration.x, 2.0f);
  EXPECT_EQ(particle.acceleration.y, 2.0f);
}

TEST(NBodySequentialTest, ApplyCentralForceZeroForce) {
  mila::SequentialNBody n_body(nullptr);
  mila::Particle particle{0.0f};
  particle.position = {1.0f, 1.0f};
  particle.acceleration = {2.0f, 2.0f};
  mila::Vector2D center{0.0f, 0.0f};

  n_body.ApplyCentralForce(center, 0.0f, particle);

  EXPECT_EQ(particle.acceleration.x, 2.0f);
  EXPECT_EQ(particle.acceleration.y, 2.0f);
}

TEST(NBodySequentialTest, ApplyCentralForceSimple) {
  mila::SequentialNBody n_body(nullptr);
  mila::Particle particle{0.0f};
  particle.position = {1.0f, 1.0f};
  mila::Vector2D center{0.0f, 0.0f};

  n_body.ApplyCentralForce(center, 2.0f, particle);

  EXPECT_EQ(particle.acceleration.x, -2.0f);
  EXPECT_EQ(particle.acceleration.y, -2.0f);
}

TEST(NBodySequentialTest, ApplyCentralForceComplex) {
  mila::SequentialNBody n_body(nullptr);
  mila::Particle particle{0.0f};
  particle.position = {1.0f, 1.0f};
  particle.acceleration = {2.0f, 2.0f};
  mila::Vector2D center{0.0f, 0.0f};

  n_body.ApplyCentralForce(center, 3.0f, particle);

  EXPECT_EQ(particle.acceleration.x, -1.0f);
  EXPECT_EQ(particle.acceleration.y, -1.0f);
}

TEST(NBodySequentialTest, ApplyDampingForceZeroVelocity) {
  mila::SequentialNBody n_body(nullptr);
  mila::Particle particle{0.0f};

  n_body.ApplyDampingForce(1.0f, particle);

  EXPECT_EQ(particle.velocity.x, 0.0f);
  EXPECT_EQ(particle.velocity.y, 0.0f);
}

TEST(NBodySequentialTest, ApplyDampingForceZeroForce) {
  mila::SequentialNBody n_body(nullptr);
  mila::Particle particle{0.0f};
  particle.velocity = {1.0f, 1.0f};

  n_body.ApplyDampingForce(0.0f, particle);

  EXPECT_EQ(particle.velocity.x, 0.0f);
  EXPECT_EQ(particle.velocity.y, 0.0f);
}

TEST(NBodySequentialTest, ApplyDampingForceSimple) {
  mila::SequentialNBody n_body(nullptr);
  mila::Particle particle{0.0f};
  particle.velocity = {1.0f, 1.0f};

  n_body.ApplyDampingForce(1.0f, particle);

  EXPECT_EQ(particle.velocity.x, 1.0f);
  EXPECT_EQ(particle.velocity.y, 1.0f);
}

TEST(NBodySequentialTest, ApplyDampingForceComplex) {
  mila::SequentialNBody n_body(nullptr);
  mila::Particle particle{0.0f};
  particle.velocity = {2.0f, 3.0f};

  n_body.ApplyDampingForce(4.0f, particle);

  EXPECT_EQ(particle.velocity.x, 8.0f);
  EXPECT_EQ(particle.velocity.y, 12.0f);
}

TEST(NBodySequentialTest, ApplyMotionWithoutAcceleration) {
  mila::SequentialNBody n_body(nullptr);
  mila::Particle particle{0.0f};
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

TEST(NBodySequentialTest, ApplyMotionWithAcceleration) {
  mila::SequentialNBody n_body(nullptr);
  mila::Particle particle{0.0f};
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

TEST(NBodySequentialTest, UpdateParticles) {
  mila::SequentialNBody n_body(nullptr);
  std::vector<mila::Particle> expected_particles = {
      {{13.42111f, 316.12225f}, {12.42111f, 314.12225f}, {0.0f, 0.0f}},
      {{95.21749f, 129.99371f}, {85.21749f, 109.99370f}, {0.0f, 0.0f}}
  };
  std::vector<mila::Particle> particles = {
      {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}},
      {{10.0f, 20.0f}, {30.0f, 40.0f}, {50.0f, 60.0f}}
  };
  mila::NBodyParameters parameters{};

  n_body.UpdateParticles(parameters, mila::Vector2D{1.0f, 1.0f}, particles);

  ASSERT_EQ(particles.size(), expected_particles.size());
  for (size_t i = 0; i < particles.size(); ++i) {
    EXPECT_NEAR(particles[i].position.x, expected_particles[i].position.x, 1e+1f);
    EXPECT_NEAR(particles[i].position.y, expected_particles[i].position.y, 1e+1f);
    EXPECT_NEAR(particles[i].velocity.x, expected_particles[i].velocity.x, 1e+1f);
    EXPECT_NEAR(particles[i].velocity.y, expected_particles[i].velocity.y, 1e+1f);
    EXPECT_NEAR(particles[i].acceleration.x, expected_particles[i].acceleration.x, 1e+1f);
    EXPECT_NEAR(particles[i].acceleration.y, expected_particles[i].acceleration.y, 1e+1f);
  }
}

TEST(NBodySequentialWithInputFileProfilerTest, GetResultsAfterUpdateParticles) {
  auto n_body = std::unique_ptr<mila::SequentialNBody>(new mila::SequentialNBody(nullptr));
  auto profiler = std::unique_ptr<mila::Profiler>(new mila::ProfilerStub());
  auto n_body_profiler = mila::SequentialNBodyProfiler(std::move(n_body), std::move(profiler), nullptr);
  std::vector<mila::Particle> particles = {
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
  const auto mean_shift = mila::SequentialNBodyApp(logger_spy);
  // const_cast due to C vs C++ string literals
  mean_shift.Run(3, const_cast<char **>(parameters));
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
