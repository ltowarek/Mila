#include "n_body_parallel_profiler.h"

mila::nbody::parallel::NBodyParallelWithInputFileProfiler::NBodyParallelWithInputFileProfiler() : NBodyParallelWithInputFileProfiler(300.0f,
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

mila::nbody::parallel::NBodyParallelWithInputFileProfiler::NBodyParallelWithInputFileProfiler(int number_of_particles, size_t platform_id, size_t device_id)
    : NBodyParallelWithInputFileProfiler(300.0f,
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

mila::nbody::parallel::NBodyParallelWithInputFileProfiler::NBodyParallelWithInputFileProfiler(float active_repulsion_force,
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
                                                                              size_t device_id) : NBodyParallelWithInputFile(active_repulsion_force,
                                                                                                                             active_repulsion_min_distance,
                                                                                                                             passive_repulsion_force,
                                                                                                                             passive_repulsion_min_distance,
                                                                                                                             damping_force,
                                                                                                                             central_force,
                                                                                                                             center,
                                                                                                                             number_of_particles,
                                                                                                                             min_position,
                                                                                                                             max_position,
                                                                                                                             platform_id,
                                                                                                                             device_id),
                                                                                                  main_result_("Frames per second"),
                                                                                                  main_duration_("Run") {
}

void mila::nbody::parallel::NBodyParallelWithInputFileProfiler::Run(const std::string &input_file) {
  auto start_time = std::chrono::high_resolution_clock::now();
  NBodyParallelWithInputFile::Run(input_file);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  results_.insert(std::pair<std::string, float>("Run", duration_us));
  results_.insert(std::pair<std::string, float>("Interactions per second", mila::utils::GetValuePerSecond((number_of_particles_ * number_of_particles_), duration)));
  results_.insert(std::pair<std::string, float>("Frames per second", mila::utils::GetValuePerSecond(number_of_frames_, duration)));
}

std::string mila::nbody::parallel::NBodyParallelWithInputFileProfiler::main_result() const {
  return main_result_;
}

std::string mila::nbody::parallel::NBodyParallelWithInputFileProfiler::main_duration() const {
  return main_duration_;
}

std::map<std::string, float> mila::nbody::parallel::NBodyParallelWithInputFileProfiler::results() const {
  return results_;
}
