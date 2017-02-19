#ifndef MILA_N_BODY_SEQUENTIAL_HPP
#define MILA_N_BODY_SEQUENTIAL_HPP

#include "logger.hpp"
#include "n_body.hpp"

namespace mila {
class SequentialNBody : public NBody {
 public:
  SequentialNBody(const std::shared_ptr<mila::Logger> logger);
  virtual ~SequentialNBody() override;

  virtual void UpdateParticles(const NBodyParameters &parameters,
                               const Vector2D &active_repulsion_force_position,
                               std::vector<Particle> &particles) override;

  void ApplyCentralForce(const Vector2D &center, const float force_value, Particle &particle) const;
  void ApplyDampingForce(const float force_value, Particle &particle) const;
  void ApplyMotion(Particle &particle) const;
  void ApplyRepulsionForce(const float force_value,
                           const float min_distance,
                           const Vector2D &position,
                           Particle &particle) const;
  void ApplyRepulsionForceBetweenParticles(const float force_value,
                                           const float min_distance,
                                           const std::vector<Particle> &particles,
                                           Particle &particle) const;
 private:
  const std::shared_ptr<mila::Logger> logger_;
};
}  // mila
#endif  // MILA_N_BODY_SEQUENTIAL_HPP
