#include "n_body.h"

bool mila::Vector2D::AreEqual(const mila::Vector2D &lhs,
                              const mila::Vector2D &rhs,
                              const double epsilon) {
  return ((fabs(lhs.x - rhs.x) < epsilon) && (fabs(lhs.y - rhs.y) < epsilon));
}

mila::NBody::~NBody() {}

std::vector<mila::Particle> mila::NBody::GenerateParticles(const size_t number_of_particles,
                                                           const float min,
                                                           const float max) {
  auto particles = std::vector<mila::Particle>();
  for (auto i = 0; i < number_of_particles; ++i) {
    auto particle = mila::Particle{0.0f};
    particle.position.x = mila::GenerateRandomValue(min, max);
    particle.position.y = mila::GenerateRandomValue(min, max);
    particles.push_back(particle);
  }
  return particles;
}
