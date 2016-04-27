#ifndef MILA_N_BODY_PARALLEL_H_
#define MILA_N_BODY_PARALLEL_H_

#include "clpp.h"

namespace mila {
namespace nbody {
namespace parallel {

struct Particle {
  cl_float2 position;
  cl_float2 velocity;
  cl_float2 acceleration;
};

class NBodyParallel {
 public:
  NBodyParallel();
  NBodyParallel(int number_of_particles, size_t platform_id, size_t device_id);
  NBodyParallel(float active_repulsion_force,
                float active_repulsion_min_distance,
                float passive_repulsion_force,
                float passive_repulsion_min_distance,
                float damping_force,
                float central_force,
                cl_float2 center,
                int number_of_particles,
                float min_position,
                float max_position,
                size_t platform_id,
                size_t device_id);

  size_t platform_id() const;
  size_t device_id() const;
  float active_repulsion_force() const;
  float active_repulsion_min_distance() const;
  float passive_repulsion_force() const;
  float passive_repulsion_min_distance() const;
  float damping_force() const;
  float central_force() const;
  cl_float2 center() const;
  int number_of_particles() const;
  float min_position() const;
  float max_position() const;
  std::vector<Particle> particles() const;
  void set_particles(std::vector<Particle> particles);
 protected:
  const size_t platform_id_;
  const size_t device_id_;
  const float active_repulsion_force_;
  const float active_repulsion_min_distance_;
  const float passive_repulsion_force_;
  const float passive_repulsion_min_distance_;
  const float damping_force_;
  const float central_force_;
  const cl_float2 center_;
  const int number_of_particles_;
  const float min_position_;
  const float max_position_;
  std::vector<Particle> particles_;
};

}  // parallel
}  // nbody
}  // mila

#endif  // MILA_N_BODY_PARALLEL_H_
