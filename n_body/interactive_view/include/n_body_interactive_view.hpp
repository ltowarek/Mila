#ifndef MILA_N_BODY_INTERACTIVE_VIEW_HPP
#define MILA_N_BODY_INTERACTIVE_VIEW_HPP

#include "GLFW/glfw3.h"
#include "n_body.hpp"
#include "utils.hpp"
#include "logger.hpp"

namespace mila {
class Vector2DFile {
 public:
  Vector2DFile(const std::string &file_name);
  void Write(const Vector2D &vector);
  void Write(const std::vector<Vector2D> &vectors);
  std::vector<Vector2D> Read() const;
  bool IsValid() const;
  void Remove() const;
 private:
  const std::string file_name_;
};

class NBodyInteractiveView {
 public:
  virtual ~NBodyInteractiveView() = default;
  virtual void Record(const mila::NBodyParameters &parameters,
                      const int number_of_frames,
                      mila::Vector2DFile &mouse_positions_file,
                      mila::Vector2DFile &output_particles_file,
                      std::vector<Particle> &particles) = 0;
  virtual bool Replay(const mila::NBodyParameters &parameters,
                      const mila::Vector2DFile &mouse_positions_file,
                      const mila::Vector2DFile &reference_particles_file,
                      std::vector<Particle> &particles) = 0;
};

class GenericNBodyInteractiveView : public NBodyInteractiveView {
 public:
  GenericNBodyInteractiveView(std::unique_ptr<mila::NBody> n_body, const std::shared_ptr<mila::Logger> logger);
  GenericNBodyInteractiveView(GenericNBodyInteractiveView &&view);
  virtual ~GenericNBodyInteractiveView();

  void Record(const mila::NBodyParameters &parameters,
              const int number_of_frames,
              mila::Vector2DFile &mouse_positions_file,
              mila::Vector2DFile &output_particles_file,
              std::vector<Particle> &particles);
  bool Replay(const mila::NBodyParameters &parameters,
              const mila::Vector2DFile &mouse_positions_file,
              const mila::Vector2DFile &reference_particles_file,
              std::vector<Particle> &particles);
 private:
  void DrawParticles(const int width, const int height, const std::vector<mila::Particle> &particles) const;
  Vector2D GetMousePosition(GLFWwindow *window) const;
  std::unique_ptr<mila::NBody> n_body_;
  const std::shared_ptr<mila::Logger> logger_;
};

class NBodyInteractiveViewStub : public NBodyInteractiveView {
 public:
  virtual ~NBodyInteractiveViewStub();
  void Record(const mila::NBodyParameters &parameters,
              const int number_of_frames,
              mila::Vector2DFile &mouse_positions_file,
              mila::Vector2DFile &output_particles_file,
              std::vector<Particle> &particles) override;
  bool Replay(const mila::NBodyParameters &parameters,
              const mila::Vector2DFile &mouse_positions_file,
              const mila::Vector2DFile &reference_particles_file,
              std::vector<Particle> &particles) override;

};
}  // mila
#endif  // MILA_N_BODY_INTERACTIVE_VIEW_HPP
