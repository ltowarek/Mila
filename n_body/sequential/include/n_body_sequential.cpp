#include "n_body_sequential.h"

mila::nbody::sequential::NBodySequential::NBodySequential(): NBodySequential(1e-5f) {
}

mila::nbody::sequential::NBodySequential::NBodySequential(float precision_): precision_(precision_) {
}

float mila::nbody::sequential::NBodySequential::precision() const {
  return precision_;
}

float mila::nbody::sequential::NBodySequential::Distance(Vector2D vector1, Vector2D vector2) {
  return sqrtf(powf(vector1.x - vector2.x, 2.0f) + powf(vector1.y - vector2.y, 2.0f));
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
