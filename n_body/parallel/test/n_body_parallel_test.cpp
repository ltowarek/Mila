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

TEST(NBodyParallelTest, GenerateParticles) {
  mila::nbody::parallel::NBodyParallel n_body;
  int number_of_particles = 5;
  float min = 10.0f;
  float max = 20.0f;

  std::vector<mila::nbody::parallel::Particle> output = n_body.GenerateParticles(number_of_particles, min, max);

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

TEST(NBodyParallelTest, Initialize) {
  mila::nbody::parallel::NBodyParallel n_body;

  EXPECT_EQ(n_body.particles().size(), 0);
  n_body.Initialize();
  EXPECT_EQ(n_body.particles().size(), n_body.number_of_particles());
}

TEST(NBodyParallelTest, UpdateParticles) {
  mila::nbody::parallel::NBodyParallel n_body;
  std::vector<mila::nbody::parallel::Particle> expected_particles = {
      {{13.42111f, 316.12225f}, {12.42111f, 314.12225f}, {0.0f, 0.0f}},
      {{95.21749f, 129.99371f}, {85.21749f, 109.99370f}, {0.0f, 0.0f}}
  };
  n_body.set_particles({
                           {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}},
                           {{10.0f, 20.0f}, {30.0f, 40.0f}, {50.0f, 60.0f}}
                       });

  n_body.InitializeOpenCL();
  n_body.UpdateParticles(cl_float2{1.0f, 1.0f});

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

TEST(NBodyParallelWithViewTest, DefaultConstructor) {
  mila::nbody::parallel::NBodyParallelWithView n_body;

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

TEST(NBodyParallelWithViewTest, NumberOfParticlesConstructor) {
  mila::nbody::parallel::NBodyParallelWithView n_body(100, 1, 2);

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

TEST(NBodyParallelWithViewTest, ComplexConstructor) {
  mila::nbody::parallel::NBodyParallelWithView n_body(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, cl_float2{7.0f, 8.0f}, 9, 10.0f, 11.0f, 12, 13);

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

TEST(NBodyParallelWithInputFileTest, DefaultConstructor) {
  mila::nbody::parallel::NBodyParallelWithInputFile n_body;

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

TEST(NBodyParallelWithInputFileTest, NumberOfParticlesConstructor) {
  mila::nbody::parallel::NBodyParallelWithInputFile n_body(100, 1, 2);

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

TEST(NBodyParallelWithInputFileTest, ComplexConstructor) {
  mila::nbody::parallel::NBodyParallelWithInputFile n_body(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, cl_float2{7.0f, 8.0f}, 9, 10.0f, 11.0f, 12, 13);

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

TEST(NBodyParallelWithInputFileTest, ParseInputFile) {
  mila::nbody::parallel::NBodyParallelWithInputFile n_body;
  std::vector<cl_float2> expected_output = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};

  std::vector<cl_float2> output = n_body.ParseInputFile("test_file.txt");

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < output.size(); ++i) {
    EXPECT_EQ(expected_output[i].x, output[i].x);
    EXPECT_EQ(expected_output[i].y, output[i].y);
  }
}
