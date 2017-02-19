#ifndef MILA_N_BODY_PARALLEL_H
#define MILA_N_BODY_PARALLEL_H

#include "clpp.h"
#include "n_body.hpp"
#include "ocl_app.hpp"
#include "utils.hpp"

namespace mila {
class ParallelNBody : public NBody {
 public:
  ParallelNBody(std::unique_ptr<OpenCLApplication> ocl_app, const std::shared_ptr<mila::Logger> logger);
  virtual ~ParallelNBody() override;

  virtual void UpdateParticles(const NBodyParameters &parameters,
                               const Vector2D &active_repulsion_force_position,
                               std::vector<Particle> &particles) override;
  virtual void Initialize();

  struct Events {
    clpp::Event read_buffer;
    clpp::Event enqueue_nd_range;
  };

  Events GetEvents() const;
 private:
  const std::shared_ptr<mila::Logger> logger_;
  const std::unique_ptr<OpenCLApplication> ocl_app_;

  Events events_;
  clpp::Kernel kernel_;
};
}  // mila
#endif  // MILA_N_BODY_PARALLEL_H
