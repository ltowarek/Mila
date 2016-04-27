#ifndef MILA_N_BODY_SEQUENTIAL_H_
#define MILA_N_BODY_SEQUENTIAL_H_

#include <cmath>
#include <vector>

#include "n_body_utils.h"

namespace mila {
namespace nbody {
namespace sequential {

struct Vector2D {
  float x;
  float y;
};

struct Particle {
  Vector2D position;
  Vector2D velocity;
  Vector2D acceleration;
};


class NBodySequential {
 public:
  NBodySequential();
  NBodySequential(float precision_);

  std::vector<Particle> GenerateParticles(int number_of_particles, float min, float max);
  Particle ApplyCentralForce(Vector2D center, float force_value, Particle particle);
  Particle ApplyDampingForce(float force_value, Particle particle);
  Particle ApplyMotion(Particle particle);
  Particle ApplyRepulsionForce(float force_value, float min_distance, Vector2D position, Particle particle);
  Particle ApplyRepulsionForceBetweenParticles(float force_value, float min_distance, Particle particle, std::vector<Particle> &particles);

  float precision() const;
 private:
  const float precision_;
};

}  // sequential
}  // nbody
}  // mila

#endif  // MILA_N_BODY_SEQUENTIAL_H_
