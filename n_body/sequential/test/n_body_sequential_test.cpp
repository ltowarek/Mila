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
}

TEST(NBodySequentialTest, ComplexConstructor) {
  mila::nbody::sequential::NBodySequential n_body(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, mila::nbody::sequential::Vector2D{7.0f, 8.0f}, 9, 10.0f, 11.0f);

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

TEST(NBodySequentialTest, Initialize) {
  mila::nbody::sequential::NBodySequential n_body;

  EXPECT_EQ(n_body.particles().size(), 0);
  n_body.Initialize();
  EXPECT_EQ(n_body.particles().size(), n_body.number_of_particles());
}

TEST(NBodySequentialTest, UpdateParticles) {
  mila::nbody::sequential::NBodySequential n_body;
  std::vector<mila::nbody::sequential::Particle> expected_particles = {
                           {{13.42111f, 316.12225f}, {12.42111f, 314.12225f}, {0.0f, 0.0f}},
                           {{95.21749f, 129.99371f}, {85.21749f, 109.99370f}, {0.0f, 0.0f}}
                       };
  n_body.set_particles({
                           {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}},
                           {{10.0f, 20.0f}, {30.0f, 40.0f}, {50.0f, 60.0f}}
                       });

  n_body.UpdateParticles(mila::nbody::sequential::Vector2D{1.0f, 1.0f});

  ASSERT_EQ(n_body.particles().size(), expected_particles.size());
  for (int i = 0; i < n_body.particles().size(); ++i) {
    EXPECT_NEAR(n_body.particles()[i].position.x, expected_particles[i].position.x, 1e-5f);
    EXPECT_NEAR(n_body.particles()[i].position.y, expected_particles[i].position.y, 1e-5f);
    EXPECT_NEAR(n_body.particles()[i].velocity.x, expected_particles[i].velocity.x, 1e-5f);
    EXPECT_NEAR(n_body.particles()[i].velocity.y, expected_particles[i].velocity.y, 1e-5f);
    EXPECT_NEAR(n_body.particles()[i].acceleration.x, expected_particles[i].acceleration.x, 1e-5f);
    EXPECT_NEAR(n_body.particles()[i].acceleration.y, expected_particles[i].acceleration.y, 1e-5f);
  }
}

TEST(NBodySequentialWithViewTest, DefaultConstructor) {
  mila::nbody::sequential::NBodySequentialWithView n_body;

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
}

TEST(NBodySequentialWithViewTest, ComplexConstructor) {
  mila::nbody::sequential::NBodySequentialWithView n_body(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, mila::nbody::sequential::Vector2D{7.0f, 8.0f}, 9, 10.0f, 11.0f);

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
}
