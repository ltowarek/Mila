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

std::vector<mila::nbody::parallel::Particle> mila::nbody::parallel::NBodyParallel::GenerateParticles(int number_of_particles,
                                                                              float min,
                                                                              float max) {
  auto particles = std::vector<mila::nbody::parallel::Particle>();
  for (auto i = 0; i < number_of_particles; ++i) {
    auto particle = mila::nbody::parallel::Particle{{0.0f}};
    particle.position.x = mila::nbody::utils::GenerateRandomValue(min, max);
    particle.position.y = mila::nbody::utils::GenerateRandomValue(min, max);
    particles.push_back(particle);
  }
  return particles;
}

std::string mila::nbody::parallel::NBodyParallel::PrepareBuildOptions() {
  std::stringstream string_stream;
  string_stream.precision(2);
  string_stream << "-D CENTER_X=" << std::fixed << center_.x << "f ";
  string_stream << "-D CENTER_Y=" << std::fixed << center_.y << "f ";
  string_stream << "-D CENTRAL_FORCE_VALUE=" << std::fixed << central_force_ << "f ";
  string_stream << "-D ACTIVE_REPULSION_FORCE_VALUE=" << std::fixed << active_repulsion_force_ << "f ";
  string_stream << "-D ACTIVE_REPULSION_FORCE_MIN_DISTANCE=" << std::fixed << active_repulsion_min_distance_ << "f ";
  string_stream << "-D PASSIVE_REPULSION_FORCE_VALUE=" << std::fixed << passive_repulsion_force_ << "f ";
  string_stream << "-D PASSIVE_REPULSION_FORCE_MIN_DISTANCE=" << std::fixed << passive_repulsion_min_distance_ << "f ";
  string_stream << "-D DAMPING_FORCE_VALUE=" << std::fixed << damping_force_ << "f";
  return string_stream.str();
}

void mila::nbody::parallel::NBodyParallel::InitializeOpenCL() {
  const auto platforms = clpp::Platform::get();
  platform_ = platforms.at(platform_id_);

  const auto devices = platform_.getAllDevices();
  device_ = devices.at(device_id_);

  context_ = clpp::Context(device_);
  queue_ = clpp::Queue(context_, device_);

  const auto source_file_name = "n_body.cl";
  const auto kernel_name = std::string("UpdateParticles");
  auto source_file = mila::utils::ReadFile(source_file_name);
  auto program = clpp::Program(context_, source_file);

  auto build_options = PrepareBuildOptions();

  try {
    program.build(device_, build_options.c_str());
  } catch(const clpp::Error& error) {
    printf("%s\n", program.getBuildLog(device_).c_str());
  }
  kernel_ = clpp::Kernel(program, kernel_name.c_str());
}

void mila::nbody::parallel::NBodyParallel::Initialize() {
  particles_ = GenerateParticles(number_of_particles_, min_position_, max_position_);
  InitializeOpenCL();
}

void mila::nbody::parallel::NBodyParallel::UpdateParticles(cl_float2 active_repulsion_force_position) {
  auto input_particles_buffer = clpp::Buffer(context_, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, particles_.size() * sizeof(particles_.at(0)), particles_.data());
  auto output_particles_buffer = clpp::Buffer(context_, CL_MEM_WRITE_ONLY, particles_.size() * sizeof(particles_.at(0)));
  auto force_position_buffer = clpp::Buffer(context_, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(active_repulsion_force_position), &active_repulsion_force_position);

  auto global_work_size = std::vector<size_t>{particles_.size()};

  kernel_.setArgs(input_particles_buffer, output_particles_buffer, force_position_buffer);
  queue_.enqueueNDRangeKernel(kernel_, global_work_size).wait();

  queue_.readBuffer(output_particles_buffer, 0, particles_.size() * sizeof(particles_.at(0)), particles_.data());
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
