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
