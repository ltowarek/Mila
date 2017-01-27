#ifndef MILA_MEAN_SHIFT_H_
#define MILA_MEAN_SHIFT_H_

#include <cstddef>
#include <vector>
#include "n_body_utils.h"

namespace mila {

struct Vector2D {
  float x;
  float y;
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

class NBodyApp {
 public:
  virtual ~NBodyApp() = 0;
  virtual void Run(int argc, char **argv) const = 0;
};
}  // mila
#endif  // MILA_UTILS_MEAN_SHIFT_H_
