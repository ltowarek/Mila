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
  NBodySequential(float active_repulsion_force_,
                  float active_repulsion_min_distance_,
                  float passive_repulsion_force_,
                  float passive_repulsion_min_distance_,
                  float damping_force_,
                  float central_force_,
                  Vector2D center_,
                  int number_of_particles_,
                  float min_position_,
                  float max_position_);

  std::vector<Particle> GenerateParticles(int number_of_particles, float min, float max);
  Particle ApplyCentralForce(Vector2D center, float force_value, Particle particle);
  Particle ApplyDampingForce(float force_value, Particle particle);
  Particle ApplyMotion(Particle particle);
  Particle ApplyRepulsionForce(float force_value, float min_distance, Vector2D position, Particle particle);
  Particle ApplyRepulsionForceBetweenParticles(float force_value, float min_distance, Particle particle, std::vector<Particle> &particles);
  void Initialize();
  void UpdateParticles(Vector2D active_repulsion_force_position);

  float active_repulsion_force() const;
  float active_repulsion_min_distance() const;
  float passive_repulsion_force() const;
  float passive_repulsion_min_distance() const;
  float damping_force() const;
  float central_force() const;
  Vector2D center() const;
  int number_of_particles() const;
  float min_position() const;
  float max_position() const;
  std::vector<Particle> particles() const;
  void set_particles(std::vector<Particle> particles);
 private:
  const float active_repulsion_force_;
  const float active_repulsion_min_distance_;
  const float passive_repulsion_force_;
  const float passive_repulsion_min_distance_;
  const float damping_force_;
  const float central_force_;
  const Vector2D center_;
  const int number_of_particles_;
  const float min_position_;
  const float max_position_;
  std::vector<Particle> particles_;
};

}  // sequential
}  // nbody
}  // mila

#endif  // MILA_N_BODY_SEQUENTIAL_H_
