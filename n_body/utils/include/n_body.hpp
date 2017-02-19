#ifndef MILA_N_BODY_H
#define MILA_N_BODY_H

#include <cstddef>
#include <vector>
#include "n_body_utils.hpp"

namespace mila {
struct Vector2D {
  float x;
  float y;

  static bool AreEqual(const Vector2D &lhs, const Vector2D &rhs, const double epsilon);
};

struct Particle {
  Vector2D position;
  Vector2D velocity;
  Vector2D acceleration;
};

struct NBodyParameters {
  float active_repulsion_force = 300.0f;
  float active_repulsion_min_distance = 100.0f;
  float passive_repulsion_force = 4.0f;
  float passive_repulsion_min_distance = 50.0f;
  float damping_force = 0.8f;
  float central_force = 0.01f;
  Vector2D center = Vector2D{512.0f, 512.0f};
};

class NBody {
 public:
  virtual ~NBody() = 0;

  virtual void UpdateParticles(const NBodyParameters &parameters,
                               const Vector2D &active_repulsion_force_position,
                               std::vector<Particle> &particles) = 0;
  static std::vector<Particle> GenerateParticles(const size_t number_of_particles,
                                                 const float min,
                                                 const float max);
};
}  // mila
#endif  // MILA_N_BODY_H
