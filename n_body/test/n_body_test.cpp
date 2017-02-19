#include "gtest/gtest.h"
#include "n_body_factories.hpp"

TEST(NBodyVector2DTest, InitializeWithSingleValue) {
  const auto vector2D = mila::Vector2D{0.0f};
  EXPECT_EQ(vector2D.x, 0.0f);
  EXPECT_EQ(vector2D.y, 0.0f);
}

TEST(NBodyVector2DTest, InitializeWithMultipleValues) {
  const auto vector2D = mila::Vector2D{1.0f, 2.0f};
  EXPECT_EQ(vector2D.x, 1.0f);
  EXPECT_EQ(vector2D.y, 2.0f);
}

TEST(NBodyParticleTest, InitializeWithSingleValue) {
  const auto particle = mila::Particle{0.0f};
  EXPECT_EQ(particle.position.x, 0.0f);
  EXPECT_EQ(particle.position.y, 0.0f);
  EXPECT_EQ(particle.velocity.x, 0.0f);
  EXPECT_EQ(particle.velocity.y, 0.0f);
  EXPECT_EQ(particle.acceleration.x, 0.0f);
  EXPECT_EQ(particle.acceleration.y, 0.0f);
}

TEST(NBodyParticleTest, InitializeWithMultipleValues) {
  const auto particle = mila::Particle{{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}};
  EXPECT_EQ(particle.position.x, 1.0f);
  EXPECT_EQ(particle.position.y, 2.0f);
  EXPECT_EQ(particle.velocity.x, 3.0f);
  EXPECT_EQ(particle.velocity.y, 4.0f);
  EXPECT_EQ(particle.acceleration.x, 5.0f);
  EXPECT_EQ(particle.acceleration.y, 6.0f);
}

TEST(NBodyTest, GenerateParticles) {
  size_t number_of_particles = 5;
  float min = 10.0f;
  float max = 20.0f;

  std::vector<mila::Particle> output = mila::NBody::GenerateParticles(number_of_particles, min, max);

  ASSERT_EQ(output.size(), number_of_particles);
  for (size_t i = 0; i < number_of_particles; ++i) {
    EXPECT_GE(output[i].position.x, min);
    EXPECT_LT(output[i].position.x, max);
    EXPECT_GE(output[i].position.y, min);
    EXPECT_LT(output[i].position.y, max);
    EXPECT_EQ(output[i].velocity.x, 0.0f);
    EXPECT_EQ(output[i].velocity.y, 0.0f);
    EXPECT_EQ(output[i].acceleration.x, 0.0f);
    EXPECT_EQ(output[i].acceleration.y, 0.0f);
  }
}

template<typename T>
std::unique_ptr<mila::NBody> CreateNBody();

template<>
std::unique_ptr<mila::NBody> CreateNBody<mila::SequentialNBody>() {
  return mila::NBodyFactory().MakeSequential(nullptr);
}

template<>
std::unique_ptr<mila::NBody> CreateNBody<mila::SequentialNBodyProfiler>() {
  auto profiler = mila::ProfilerFactory().MakeChrono(nullptr);
  return mila::NBodyFactory().MakeSequentialProfiler(std::move(profiler), nullptr);
}

template<>
std::unique_ptr<mila::NBody> CreateNBody<mila::ParallelNBody>() {
  auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, nullptr);
  return mila::NBodyFactory().MakeParallel(std::move(ocl_app), nullptr);
}

template<>
std::unique_ptr<mila::NBody> CreateNBody<mila::ParallelNBodyProfiler>() {
  auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, nullptr);
  auto profiler = mila::ProfilerFactory().MakeChrono(nullptr);
  return mila::NBodyFactory().MakeParallelProfiler(std::move(ocl_app), std::move(profiler), nullptr);
}

template<typename T>
class NBodyTest : public testing::Test {
 protected:
  NBodyTest() : n_body_(std::move(CreateNBody<T>())) {}
  std::unique_ptr<mila::NBody> n_body_;
};

typedef testing::Types<mila::SequentialNBody,
                       mila::SequentialNBodyProfiler,
                       mila::ParallelNBody,
                       mila::ParallelNBodyProfiler> NBodyImplementations;

TYPED_TEST_CASE(NBodyTest, NBodyImplementations);

TYPED_TEST(NBodyTest, RunSimple) {
  const auto expected_particles = std::vector<mila::Particle>{
      {{13.42111f, 316.12225f}, {12.42111f, 314.12225f}, {0.0f, 0.0f}},
      {{95.21749f, 129.99371f}, {85.21749f, 109.99370f}, {0.0f, 0.0f}}
  };
  auto particles = std::vector<mila::Particle>{
      {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}},
      {{10.0f, 20.0f}, {30.0f, 40.0f}, {50.0f, 60.0f}}
  };
  const auto parameters = mila::NBodyParameters{};

  this->n_body_->UpdateParticles(parameters, mila::Vector2D{1.0f, 1.0f}, particles);

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
