#include "gtest/gtest.h"
#include "n_body_sequential.h"

TEST(NBodyVector2DTest, InitializeWithSingleValue) {
  mila::nbody::sequential::Vector2D vector2D = {0.0f};
  EXPECT_EQ(vector2D.x, 0.0f);
  EXPECT_EQ(vector2D.y, 0.0f);
}

TEST(NBodyVector2DTest, InitializeWithMultipleValues) {
  mila::nbody::sequential::Vector2D vector2D = {1.0f, 2.0f};
  EXPECT_EQ(vector2D.x, 1.0f);
  EXPECT_EQ(vector2D.y, 2.0f);
}

TEST(NBodySequentialTest, DistanceZero) {
  mila::nbody::sequential::NBodySequential n_body;
  mila::nbody::sequential::Vector2D vector1 = {0.0f};
  mila::nbody::sequential::Vector2D vector2 = {0.0f};
  EXPECT_EQ(n_body.Distance(vector1, vector2), 0.0f);
}

TEST(NBodySequentialTest, DistanceComplex) {
  mila::nbody::sequential::NBodySequential n_body;
  mila::nbody::sequential::Vector2D vector1 = {3.0f, 2.0f};
  mila::nbody::sequential::Vector2D vector2 = {5.0f, -1.0f};
  EXPECT_NEAR(n_body.Distance(vector1, vector2), 3.60555f, 1e-5f);
}

TEST(NBodyParticleTest, InitializeWithSingleValue) {
  mila::nbody::sequential::Particle particle = {0.0f};
  EXPECT_EQ(particle.position.x, 0.0f);
  EXPECT_EQ(particle.position.y, 0.0f);
  EXPECT_EQ(particle.velocity.x, 0.0f);
  EXPECT_EQ(particle.velocity.y, 0.0f);
  EXPECT_EQ(particle.acceleration.x, 0.0f);
  EXPECT_EQ(particle.acceleration.y, 0.0f);
}

TEST(NBodyParticleTest, InitializeWithMultipleValues) {
  mila::nbody::sequential::Particle particle = {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}};
  EXPECT_EQ(particle.position.x, 1.0f);
  EXPECT_EQ(particle.position.y, 2.0f);
  EXPECT_EQ(particle.velocity.x, 3.0f);
  EXPECT_EQ(particle.velocity.y, 4.0f);
  EXPECT_EQ(particle.acceleration.x, 5.0f);
  EXPECT_EQ(particle.acceleration.y, 6.0f);
}

TEST(NBodySequentialTest, GenerateParticles) {
  mila::nbody::sequential::NBodySequential n_body;
  int number_of_particles = 5;
  float min = 10.0f;
  float max = 20.0f;

  std::vector<mila::nbody::sequential::Particle> output = n_body.GenerateParticles(number_of_particles, min, max);

  ASSERT_EQ(output.size(), number_of_particles);
  for (int i = 0; i < number_of_particles; ++i) {
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

TEST(NBodySequentialTest, DefaultConstructor) {
  mila::nbody::sequential::NBodySequential n_body;
  EXPECT_EQ(n_body.precision(), 1e-5f);
}

TEST(NBodySequentialTest, PrecisionConstructor) {
  mila::nbody::sequential::NBodySequential n_body(1e-7);
  EXPECT_EQ(n_body.precision(), 1e-7f);
}

TEST(NBodySequentialTest, ApplyCentralForceZeroDistance) {
  mila::nbody::sequential::NBodySequential n_body;
  mila::nbody::sequential::Particle particle{0.0f};
  particle.acceleration = {2.0f, 2.0f};
  mila::nbody::sequential::Vector2D center{0.0f, 0.0f};

  mila::nbody::sequential::Particle output = n_body.ApplyCentralForce(center, 3.0f, particle);

  EXPECT_EQ(output.acceleration.x, 2.0f);
  EXPECT_EQ(output.acceleration.y, 2.0f);
}

TEST(NBodySequentialTest, ApplyCentralForceZeroForce) {
  mila::nbody::sequential::NBodySequential n_body;
  mila::nbody::sequential::Particle particle{0.0f};
  particle.position = {1.0f, 1.0f};
  particle.acceleration = {2.0f, 2.0f};
  mila::nbody::sequential::Vector2D center{0.0f, 0.0f};

  mila::nbody::sequential::Particle output = n_body.ApplyCentralForce(center, 0.0f, particle);

  EXPECT_EQ(output.acceleration.x, 2.0f);
  EXPECT_EQ(output.acceleration.y, 2.0f);
}

TEST(NBodySequentialTest, ApplyCentralForceSimple) {
  mila::nbody::sequential::NBodySequential n_body;
  mila::nbody::sequential::Particle particle{0.0f};
  particle.position = {1.0f, 1.0f};
  mila::nbody::sequential::Vector2D center{0.0f, 0.0f};

  mila::nbody::sequential::Particle output = n_body.ApplyCentralForce(center, 2.0f, particle);

  EXPECT_EQ(output.acceleration.x, -2.0f);
  EXPECT_EQ(output.acceleration.y, -2.0f);
}

TEST(NBodySequentialTest, ApplyCentralForceComplex) {
  mila::nbody::sequential::NBodySequential n_body;
  mila::nbody::sequential::Particle particle{0.0f};
  particle.position = {1.0f, 1.0f};
  particle.acceleration = {2.0f, 2.0f};
  mila::nbody::sequential::Vector2D center{0.0f, 0.0f};

  mila::nbody::sequential::Particle output = n_body.ApplyCentralForce(center, 3.0f, particle);

  EXPECT_EQ(output.acceleration.x, -1.0f);
  EXPECT_EQ(output.acceleration.y, -1.0f);
}

TEST(NBodySequentialTest, ApplyDampingForceZeroVelocity) {
  mila::nbody::sequential::NBodySequential n_body;
  mila::nbody::sequential::Particle particle{0.0f};

  mila::nbody::sequential::Particle output = n_body.ApplyDampingForce(1.0f, particle);

  EXPECT_EQ(output.velocity.x, 0.0f);
  EXPECT_EQ(output.velocity.y, 0.0f);
}

TEST(NBodySequentialTest, ApplyDampingForceZeroForce) {
  mila::nbody::sequential::NBodySequential n_body;
  mila::nbody::sequential::Particle particle{0.0f};
  particle.velocity = {1.0f, 1.0f};

  mila::nbody::sequential::Particle output = n_body.ApplyDampingForce(0.0f, particle);

  EXPECT_EQ(output.velocity.x, 0.0f);
  EXPECT_EQ(output.velocity.y, 0.0f);
}

TEST(NBodySequentialTest, ApplyDampingForceSimple) {
  mila::nbody::sequential::NBodySequential n_body;
  mila::nbody::sequential::Particle particle{0.0f};
  particle.velocity = {1.0f, 1.0f};

  mila::nbody::sequential::Particle output = n_body.ApplyDampingForce(1.0f, particle);

  EXPECT_EQ(output.velocity.x, 1.0f);
  EXPECT_EQ(output.velocity.y, 1.0f);
}

TEST(NBodySequentialTest, ApplyDampingForceComplex) {
  mila::nbody::sequential::NBodySequential n_body;
  mila::nbody::sequential::Particle particle{0.0f};
  particle.velocity = {2.0f, 3.0f};

  mila::nbody::sequential::Particle output = n_body.ApplyDampingForce(4.0f, particle);

  EXPECT_EQ(output.velocity.x, 8.0f);
  EXPECT_EQ(output.velocity.y, 12.0f);
}

TEST(NBodySequentialTest, ApplyMotionWithoutAcceleration) {
  mila::nbody::sequential::NBodySequential n_body;
  mila::nbody::sequential::Particle particle{0.0f};
  particle.position = {1.0f, 1.0f};
  particle.velocity = {1.0f, 1.0f};

  mila::nbody::sequential::Particle output = n_body.ApplyMotion(particle);

  EXPECT_EQ(output.position.x, 2.0f);
  EXPECT_EQ(output.position.y, 2.0f);
  EXPECT_EQ(output.velocity.x, 1.0f);
  EXPECT_EQ(output.velocity.y, 1.0f);
  EXPECT_EQ(output.acceleration.x, 0.0f);
  EXPECT_EQ(output.acceleration.y, 0.0f);
}

TEST(NBodySequentialTest, ApplyMotionWithAcceleration) {
  mila::nbody::sequential::NBodySequential n_body;
  mila::nbody::sequential::Particle particle{0.0f};
  particle.position = {1.0f, 1.0f};
  particle.velocity = {1.0f, 1.0f};
  particle.acceleration = {2.0f, 2.0f};

  mila::nbody::sequential::Particle output = n_body.ApplyMotion(particle);

  EXPECT_EQ(output.position.x, 4.0f);
  EXPECT_EQ(output.position.y, 4.0f);
  EXPECT_EQ(output.velocity.x, 3.0f);
  EXPECT_EQ(output.velocity.y, 3.0f);
  EXPECT_EQ(output.acceleration.x, 0.0f);
  EXPECT_EQ(output.acceleration.y, 0.0f);
}
