#include "gtest/gtest.h"
#include "n_body_parallel.h"
#include "n_body_parallel_profiler.h"

TEST(NBodyParticleTest, InitializeWithSingleValue) {
  mila::nbody::parallel::Particle particle = mila::nbody::parallel::Particle{{0.0f}};
  EXPECT_EQ(particle.position.x, 0.0f);
  EXPECT_EQ(particle.position.y, 0.0f);
  EXPECT_EQ(particle.velocity.x, 0.0f);
  EXPECT_EQ(particle.velocity.y, 0.0f);
  EXPECT_EQ(particle.acceleration.x, 0.0f);
  EXPECT_EQ(particle.acceleration.y, 0.0f);
}

TEST(NBodyParticleTest, InitializeWithMultipleValues) {
  mila::nbody::parallel::Particle particle = {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}};
  EXPECT_EQ(particle.position.x, 1.0f);
  EXPECT_EQ(particle.position.y, 2.0f);
  EXPECT_EQ(particle.velocity.x, 3.0f);
  EXPECT_EQ(particle.velocity.y, 4.0f);
  EXPECT_EQ(particle.acceleration.x, 5.0f);
  EXPECT_EQ(particle.acceleration.y, 6.0f);
}

TEST(NBodyParallelTest, DefaultConstructor) {
  mila::nbody::parallel::NBodyParallel n_body;

  EXPECT_EQ(n_body.active_repulsion_force(), 300.0f);
  EXPECT_EQ(n_body.active_repulsion_min_distance(), 100.0f);
  EXPECT_EQ(n_body.passive_repulsion_force(), 4.0f);
  EXPECT_EQ(n_body.passive_repulsion_min_distance(), 50.0f);
  EXPECT_EQ(n_body.damping_force(), 0.8f);
  EXPECT_EQ(n_body.central_force(), 0.01f);
  EXPECT_EQ(n_body.center().x, 512.0f);
  EXPECT_EQ(n_body.center().y, 512.0f);
  EXPECT_EQ(n_body.number_of_particles(), 500);
  EXPECT_EQ(n_body.min_position(), 0.0f);
  EXPECT_EQ(n_body.max_position(), 1024.0f);
  EXPECT_EQ(n_body.platform_id(), 0);
  EXPECT_EQ(n_body.device_id(), 0);
}

TEST(NBodyParallelTest, NumberOfParticlesConstructor) {
  mila::nbody::parallel::NBodyParallel n_body(100, 1, 2);

  EXPECT_EQ(n_body.active_repulsion_force(), 300.0f);
  EXPECT_EQ(n_body.active_repulsion_min_distance(), 100.0f);
  EXPECT_EQ(n_body.passive_repulsion_force(), 4.0f);
  EXPECT_EQ(n_body.passive_repulsion_min_distance(), 50.0f);
  EXPECT_EQ(n_body.damping_force(), 0.8f);
  EXPECT_EQ(n_body.central_force(), 0.01f);
  EXPECT_EQ(n_body.center().x, 512.0f);
  EXPECT_EQ(n_body.center().y, 512.0f);
  EXPECT_EQ(n_body.number_of_particles(), 100);
  EXPECT_EQ(n_body.min_position(), 0.0f);
  EXPECT_EQ(n_body.max_position(), 1024.0f);
  EXPECT_EQ(n_body.platform_id(), 1);
  EXPECT_EQ(n_body.device_id(), 2);
}

TEST(NBodyParallelTest, ComplexConstructor) {
  mila::nbody::parallel::NBodyParallel n_body(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, cl_float2{7.0f, 8.0f}, 9, 10.0f, 11.0f, 12, 13);

  EXPECT_EQ(n_body.active_repulsion_force(), 1.0f);
  EXPECT_EQ(n_body.active_repulsion_min_distance(), 2.0f);
  EXPECT_EQ(n_body.passive_repulsion_force(), 3.0f);
  EXPECT_EQ(n_body.passive_repulsion_min_distance(), 4.0f);
  EXPECT_EQ(n_body.damping_force(), 5.0f);
  EXPECT_EQ(n_body.central_force(), 6.0f);
  EXPECT_EQ(n_body.center().x, 7.0f);
  EXPECT_EQ(n_body.center().y, 8.0f);
  EXPECT_EQ(n_body.number_of_particles(), 9);
  EXPECT_EQ(n_body.min_position(), 10.0f);
  EXPECT_EQ(n_body.max_position(), 11.0f);
  EXPECT_EQ(n_body.platform_id(), 12);
  EXPECT_EQ(n_body.device_id(), 13);
}
