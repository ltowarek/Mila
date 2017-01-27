#include "n_body.h"

mila::NBody::~NBody() {}

std::vector<mila::Particle> mila::NBody::GenerateParticles(const size_t number_of_particles,
                                                           const float min,
                                                           const float max) {
  auto particles = std::vector<mila::Particle>();
  for (auto i = 0; i < number_of_particles; ++i) {
    auto particle = mila::Particle{0.0f};
    particle.position.x = mila::nbody::utils::GenerateRandomValue(min, max);
    particle.position.y = mila::nbody::utils::GenerateRandomValue(min, max);
    particles.push_back(particle);
  }
  return particles;
}

mila::NBodyApp::~NBodyApp() {}
