#include "n_body_parallel.h"

mila::ParallelNBody::ParallelNBody(std::unique_ptr<mila::OpenCLApplication> ocl_app,
                                   const std::shared_ptr<mila::Logger> logger) :
    ocl_app_(std::move(ocl_app)), logger_(logger) {
}

mila::ParallelNBody::~ParallelNBody() {
}

void mila::ParallelNBody::Initialize() {
  kernel_ = ocl_app_->CreateKernel("UpdateParticles", "n_body.cl");
}

void mila::ParallelNBody::UpdateParticles(const NBodyParameters &parameters,
                                          const Vector2D &active_repulsion_force_position,
                                          std::vector<Particle> &particles) {
  // Vector2D and Particle do not use OCL types so there is no guarantee that they will be portable between systems

  const auto input_particles_buffer = clpp::Buffer(ocl_app_->GetContext(),
                                                   CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                                   particles.size() * sizeof(particles[0]),
                                                   particles.data());
  const auto output_particles_buffer = clpp::Buffer(ocl_app_->GetContext(),
                                                    CL_MEM_WRITE_ONLY,
                                                    particles.size() * sizeof(particles[0]));
  const auto parameters_buffer = clpp::Buffer(ocl_app_->GetContext(),
                                              CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                              sizeof(parameters),
                                              const_cast<NBodyParameters *>(&parameters));
  const auto force_position_buffer = clpp::Buffer(ocl_app_->GetContext(),
                                                  CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                                  sizeof(active_repulsion_force_position),
                                                  const_cast<Vector2D *>(&active_repulsion_force_position));

  const auto global_work_size = std::vector<size_t>{particles.size()};

  kernel_.setArgs(input_particles_buffer, output_particles_buffer, parameters_buffer, force_position_buffer);
  events_.enqueue_nd_range = ocl_app_->GetQueue().enqueueNDRangeKernel(kernel_, global_work_size);

  events_.read_buffer = ocl_app_->GetQueue().enqueueReadBuffer(output_particles_buffer,
                                                               0,
                                                               particles.size() * sizeof(particles[0]),
                                                               particles.data(),
                                                               {events_.enqueue_nd_range});
  ocl_app_->GetQueue().finish();
}

mila::ParallelNBody::Events mila::ParallelNBody::GetEvents() const {
  return events_;
}
