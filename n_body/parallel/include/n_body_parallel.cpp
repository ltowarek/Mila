#include "n_body_parallel.h"

mila::nbody::parallel::NBodyParallel::NBodyParallel() : NBodyParallel(300.0f,
                                                                      100.0f,
                                                                      4.0f,
                                                                      50.0f,
                                                                      0.8f,
                                                                      0.01f,
                                                                      cl_float2{512.0f, 512.0f},
                                                                      500,
                                                                      0.0f,
                                                                      1024.0f,
                                                                      0,
                                                                      0) {
}

mila::nbody::parallel::NBodyParallel::NBodyParallel(int number_of_particles, size_t platform_id, size_t device_id)
    : NBodyParallel(300.0f,
                    100.0f,
                    4.0f,
                    50.0f,
                    0.8f,
                    0.01f,
                    cl_float2{512.0f, 512.0f},
                    number_of_particles,
                    0.0f,
                    1024.0f,
                    platform_id,
                    device_id) {
}

mila::nbody::parallel::NBodyParallel::NBodyParallel(float active_repulsion_force,
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
                                                    size_t device_id) : active_repulsion_force_(active_repulsion_force),
                                                                        active_repulsion_min_distance_(active_repulsion_min_distance),
                                                                        passive_repulsion_force_(passive_repulsion_force),
                                                                        passive_repulsion_min_distance_(passive_repulsion_min_distance),
                                                                        damping_force_(damping_force),
                                                                        central_force_(central_force),
                                                                        center_(center),
                                                                        number_of_particles_(number_of_particles),
                                                                        min_position_(min_position),
                                                                        max_position_(max_position),
                                                                        platform_id_(platform_id),
                                                                        device_id_(device_id) {
}

float mila::nbody::parallel::NBodyParallel::active_repulsion_force() const {
  return active_repulsion_force_;
}

float mila::nbody::parallel::NBodyParallel::active_repulsion_min_distance() const {
  return active_repulsion_min_distance_;
}

float mila::nbody::parallel::NBodyParallel::passive_repulsion_force() const {
  return passive_repulsion_force_;
}

float mila::nbody::parallel::NBodyParallel::passive_repulsion_min_distance() const {
  return passive_repulsion_min_distance_;
}

float mila::nbody::parallel::NBodyParallel::damping_force() const {
  return damping_force_;
}

float mila::nbody::parallel::NBodyParallel::central_force() const {
  return central_force_;
}

cl_float2 mila::nbody::parallel::NBodyParallel::center() const {
  return center_;
}

int mila::nbody::parallel::NBodyParallel::number_of_particles() const {
  return number_of_particles_;
}

float mila::nbody::parallel::NBodyParallel::min_position() const {
  return min_position_;
}

float mila::nbody::parallel::NBodyParallel::max_position() const {
  return max_position_;
}

std::vector<mila::nbody::parallel::Particle> mila::nbody::parallel::NBodyParallel::particles() const {
  return particles_;
}

void mila::nbody::parallel::NBodyParallel::set_particles(std::vector<Particle> particles) {
  particles_ = particles;
}

size_t mila::nbody::parallel::NBodyParallel::platform_id() const {
  return platform_id_;
}

size_t mila::nbody::parallel::NBodyParallel::device_id() const {
  return device_id_;
}


