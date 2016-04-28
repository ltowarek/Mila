#ifndef MILA_N_BODY_PARALLEL_H_
#define MILA_N_BODY_PARALLEL_H_

#include <sstream>

#include "clpp.h"
#include "GLFW/glfw3.h"
#include "utils.h"
#include "n_body_utils.h"

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

  std::vector<Particle> GenerateParticles(int number_of_particles, float min, float max);
  void InitializeOpenCL();
  void Initialize();
  void UpdateParticles(cl_float2 active_repulsion_force_position);

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
  clpp::Platform platform() const;
  clpp::Device device() const;
 protected:
  std::string PrepareBuildOptions();

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
  clpp::Platform platform_;
  clpp::Device device_;
  clpp::Context context_;
  clpp::Queue queue_;
  clpp::Kernel kernel_;
};

class NBodyParallelWithView: public NBodyParallel {
 public:
  NBodyParallelWithView();
  NBodyParallelWithView(int number_of_particles, size_t platform_id, size_t device_id);
  NBodyParallelWithView(float active_repulsion_force,
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

  virtual void Run();
};

class NBodyParallelWithInputFile: public NBodyParallelWithView {
 public:
  NBodyParallelWithInputFile();
  NBodyParallelWithInputFile(int number_of_particles, size_t platform_id, size_t device_id);
  NBodyParallelWithInputFile(float active_repulsion_force,
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

  std::vector<cl_float2> ParseInputFile(const std::string &input_file);
  virtual void Run(const std::string &input_file);
  virtual void Run() override;
};

}  // parallel
}  // nbody
}  // mila

#endif  // MILA_N_BODY_PARALLEL_H_
