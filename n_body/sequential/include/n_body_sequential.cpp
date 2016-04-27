#include "n_body_sequential.h"

mila::nbody::sequential::NBodySequential::NBodySequential(): NBodySequential(300.0f, 100.0f, 4.0f, 50.0f, 0.8f, 0.01f,
                                                                             Vector2D{512.0f, 512.0f}, 500, 0.0f, 1024.0f) {
}

mila::nbody::sequential::NBodySequential::NBodySequential(float active_repulsion_force,
                float active_repulsion_min_distance,
                float passive_repulsion_force,
                float passive_repulsion_min_distance,
                float damping_force,
                float central_force,
                Vector2D center,
                int number_of_particles,
                float min_position,
                float max_position)
    : active_repulsion_force_(active_repulsion_force),
      active_repulsion_min_distance_(active_repulsion_min_distance),
      passive_repulsion_force_(passive_repulsion_force),
      passive_repulsion_min_distance_(passive_repulsion_min_distance), damping_force_(damping_force),
      central_force_(central_force), center_(center), number_of_particles_(number_of_particles),
      min_position_(min_position), max_position_(max_position) {
}

mila::nbody::sequential::Particle mila::nbody::sequential::NBodySequential::ApplyCentralForce(Vector2D center,
                                                                                              float force_value,
                                                                                              Particle particle) {
  auto output = particle;
  output.acceleration.x += (center.x - particle.position.x) * force_value;
  output.acceleration.y += (center.y - particle.position.y) * force_value;
  return output;
}

mila::nbody::sequential::Particle mila::nbody::sequential::NBodySequential::ApplyDampingForce(float force_value, Particle particle) {
  auto output = particle;
  output.velocity.x *= force_value;
  output.velocity.y *= force_value;
  return output;
}

mila::nbody::sequential::Particle mila::nbody::sequential::NBodySequential::ApplyMotion(Particle particle) {
  auto output = particle;
  output.velocity.x += output.acceleration.x;
  output.velocity.y += output.acceleration.y;
  output.position.x += output.velocity.x;
  output.position.y += output.velocity.y;
  output.acceleration.x = 0.0f;
  output.acceleration.y = 0.0f;
  return output;
}

mila::nbody::sequential::Particle mila::nbody::sequential::NBodySequential::ApplyRepulsionForceBetweenParticles(float force_value,
                                                                                                                float min_distance,
                                                                                                                Particle particle,
                                                                                                                std::vector<Particle> &particles) {
  auto output = particle;
  for (auto i = 0; i < particles.size(); ++i) {
    auto distance_vector = Vector2D{particle.position.x - particles[i].position.x,
                                    particle.position.y - particles[i].position.y};
    auto distance_squared = distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y;
    if (distance_squared < min_distance * min_distance) {
      if (distance_squared < 1.0f) {
        distance_squared = 1.0f;
      }
      auto inverted_distance_squared = 1.0f / distance_squared;
      output.acceleration.x += distance_vector.x * force_value * inverted_distance_squared;
      output.acceleration.y += distance_vector.y * force_value * inverted_distance_squared;
      particles[i].acceleration.x -= distance_vector.x * force_value * inverted_distance_squared;
      particles[i].acceleration.y -= distance_vector.y * force_value * inverted_distance_squared;
    }
  }
  return output;
}

mila::nbody::sequential::Particle mila::nbody::sequential::NBodySequential::ApplyRepulsionForce(float force_value,
                                                                                                float min_distance,
                                                                                                Vector2D position,
                                                                                                Particle particle) {
  auto output = particle;
  auto distance_vector = Vector2D{position.x - particle.position.x,
                                  position.y - particle.position.y};
  auto distance_squared = distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y;
  if (distance_squared < min_distance * min_distance) {
    auto inverted_distance_squared = 1.0f / distance_squared;
    output.acceleration.x -= distance_vector.x * force_value * inverted_distance_squared;
    output.acceleration.y -= distance_vector.y * force_value * inverted_distance_squared;
  }
  return output;
}

std::vector<mila::nbody::sequential::Particle> mila::nbody::sequential::NBodySequential::GenerateParticles(int number_of_particles,
                                                                                                           float min,
                                                                                                           float max) {
  auto particles = std::vector<mila::nbody::sequential::Particle>();
  for (auto i = 0; i < number_of_particles; ++i) {
    auto particle = mila::nbody::sequential::Particle{0.0f};
    particle.position.x = mila::nbody::utils::GenerateRandomValue(min, max);
    particle.position.y = mila::nbody::utils::GenerateRandomValue(min, max);
    particles.push_back(particle);
  }
  return particles;
}

float mila::nbody::sequential::NBodySequential::active_repulsion_force() const {
  return active_repulsion_force_;
}

float mila::nbody::sequential::NBodySequential::active_repulsion_min_distance() const {
  return active_repulsion_min_distance_;
}

float mila::nbody::sequential::NBodySequential::passive_repulsion_force() const {
  return passive_repulsion_force_;
}

float mila::nbody::sequential::NBodySequential::passive_repulsion_min_distance() const {
  return passive_repulsion_min_distance_;
}

float mila::nbody::sequential::NBodySequential::damping_force() const {
  return damping_force_;
}

float mila::nbody::sequential::NBodySequential::central_force() const {
  return central_force_;
}

mila::nbody::sequential::Vector2D mila::nbody::sequential::NBodySequential::center() const {
  return center_;
}

int mila::nbody::sequential::NBodySequential::number_of_particles() const {
  return number_of_particles_;
}

float mila::nbody::sequential::NBodySequential::min_position() const {
  return min_position_;
}

float mila::nbody::sequential::NBodySequential::max_position() const {
  return max_position_;
}
