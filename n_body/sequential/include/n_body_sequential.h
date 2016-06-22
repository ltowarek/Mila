#ifndef MILA_N_BODY_SEQUENTIAL_H_
#define MILA_N_BODY_SEQUENTIAL_H_

#include <cmath>
#include <fstream>
#include <vector>

#include <GLFW/glfw3.h>
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
 protected:
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

class NBodySequentialWithView: public NBodySequential {
 public:
  NBodySequentialWithView();
  NBodySequentialWithView(float active_repulsion_force_,
                          float active_repulsion_min_distance_,
                          float passive_repulsion_force_,
                          float passive_repulsion_min_distance_,
                          float damping_force_,
                          float central_force_,
                          Vector2D center_,
                          int number_of_particles_,
                          float min_position_,
                          float max_position_);

  virtual void Run();
};

class NBodySequentialWithInputFile: public NBodySequentialWithView {
 public:
  NBodySequentialWithInputFile();
  NBodySequentialWithInputFile(int number_of_particles);
  NBodySequentialWithInputFile(float active_repulsion_force_,
                               float active_repulsion_min_distance_,
                               float passive_repulsion_force_,
                               float passive_repulsion_min_distance_,
                               float damping_force_,
                               float central_force_,
                               Vector2D center_,
                               int number_of_particles_,
                               float min_position_,
                               float max_position_);

  std::vector<Vector2D> ParseInputFile(const std::string &input_file);
  virtual void Run(const std::string &input_file);
  virtual void Run() override;
};

}  // sequential
}  // nbody
}  // mila

#endif  // MILA_N_BODY_SEQUENTIAL_H_