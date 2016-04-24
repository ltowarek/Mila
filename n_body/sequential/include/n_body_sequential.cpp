#include "n_body_sequential.h"

std::vector<mila::nbody::sequential::Particle> mila::nbody::sequential::GenerateParticles(int number_of_particles, float min, float max) {
  auto particles = std::vector<mila::nbody::sequential::Particle>();
  for (auto i = 0; i < number_of_particles; ++i) {
    auto particle = mila::nbody::sequential::Particle{0.0f};
    particle.position.x = mila::nbody::utils::GenerateRandomValue(min, max);
    particle.position.y = mila::nbody::utils::GenerateRandomValue(min, max);
    particles.push_back(particle);
  }
  return particles;
}

mila::nbody::sequential::NBodySequential::NBodySequential(): NBodySequential(1e-5) {
}

mila::nbody::sequential::NBodySequential::NBodySequential(float precision_): precision_(precision_) {
}

float mila::nbody::sequential::NBodySequential::precision() const {
  return precision_;
}

float mila::nbody::sequential::NBodySequential::Distance(Vector2D vector1, Vector2D vector2) {
  return sqrtf(powf(vector1.x - vector2.x, 2.0f) + powf(vector1.y - vector2.y, 2.0f));
}
