#include "n_body_sequential.h"

mila::SequentialNBody::SequentialNBody(const std::shared_ptr<mila::Logger> logger) : logger_(logger) {
}

mila::SequentialNBody::~SequentialNBody() {
}

void mila::SequentialNBody::ApplyCentralForce(const Vector2D &center,
                                              const float force_value,
                                              Particle &particle) const {
  particle.acceleration.x += (center.x - particle.position.x) * force_value;
  particle.acceleration.y += (center.y - particle.position.y) * force_value;
}

void mila::SequentialNBody::ApplyDampingForce(const float force_value, Particle &particle) const {
  particle.velocity.x *= force_value;
  particle.velocity.y *= force_value;
}

void mila::SequentialNBody::ApplyMotion(Particle &particle) const {
  particle.velocity.x += particle.acceleration.x;
  particle.velocity.y += particle.acceleration.y;
  particle.position.x += particle.velocity.x;
  particle.position.y += particle.velocity.y;
  particle.acceleration.x = 0.0f;
  particle.acceleration.y = 0.0f;
}

void mila::SequentialNBody::ApplyRepulsionForceBetweenParticles(const float force_value,
                                                                const float min_distance,
                                                                const std::vector<Particle> &particles,
                                                                Particle &particle) const {
  for (auto i = 0; i < particles.size(); ++i) {
    const auto distance_vector = Vector2D{particle.position.x - particles[i].position.x,
                                          particle.position.y - particles[i].position.y};
    auto distance_squared = distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y;
    if (distance_squared < min_distance * min_distance) {
      if (distance_squared < 1.0f) {
        distance_squared = 1.0f;
      }
      const auto inverted_distance_squared = 1.0f / distance_squared;
      particle.acceleration.x += distance_vector.x * force_value * inverted_distance_squared;
      particle.acceleration.y += distance_vector.y * force_value * inverted_distance_squared;
    }
  }
}

void mila::SequentialNBody::ApplyRepulsionForce(const float force_value,
                                                const float min_distance,
                                                const Vector2D &position,
                                                Particle &particle) const {
  const auto distance_vector = Vector2D{position.x - particle.position.x,
                                        position.y - particle.position.y};
  const auto distance_squared = distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y;
  if (distance_squared < min_distance * min_distance) {
    const auto inverted_distance_squared = 1.0f / distance_squared;
    particle.acceleration.x -= distance_vector.x * force_value * inverted_distance_squared;
    particle.acceleration.y -= distance_vector.y * force_value * inverted_distance_squared;
  }
}

void mila::SequentialNBody::UpdateParticles(const NBodyParameters &parameters,
                                            const Vector2D &active_repulsion_force_position,
                                            std::vector<Particle> &particles) {
  for (auto i = 0; i < particles.size(); ++i) {
    ApplyRepulsionForce(parameters.active_repulsion_force,
                        parameters.active_repulsion_min_distance,
                        active_repulsion_force_position,
                        particles[i]);
    ApplyCentralForce(parameters.center, parameters.central_force, particles[i]);
    ApplyRepulsionForceBetweenParticles(parameters.passive_repulsion_force,
                                        parameters.passive_repulsion_min_distance,
                                        particles,
                                        particles[i]);
    ApplyDampingForce(parameters.damping_force, particles[i]);
    ApplyMotion(particles[i]);
  }
}
