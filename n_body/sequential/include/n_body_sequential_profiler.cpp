#include "n_body_sequential_profiler.h"

mila::nbody::sequential::NBodySequentialWithInputFileProfiler::NBodySequentialWithInputFileProfiler(): NBodySequentialWithInputFileProfiler(300.0f, 100.0f, 4.0f, 50.0f, 0.8f, 0.01f,
                                                                                                                    Vector2D{512.0f, 512.0f}, 500, 0.0f, 1024.0f) {
}

mila::nbody::sequential::NBodySequentialWithInputFileProfiler::NBodySequentialWithInputFileProfiler(int number_of_particles): NBodySequentialWithInputFileProfiler(300.0f, 100.0f, 4.0f, 50.0f, 0.8f, 0.01f,
                                                                                                                                           Vector2D{512.0f, 512.0f}, number_of_particles, 0.0f, 1024.0f) {
}

mila::nbody::sequential::NBodySequentialWithInputFileProfiler::NBodySequentialWithInputFileProfiler(float active_repulsion_force,
                                                                                    float active_repulsion_min_distance,
                                                                                    float passive_repulsion_force,
                                                                                    float passive_repulsion_min_distance,
                                                                                    float damping_force,
                                                                                    float central_force,
                                                                                    Vector2D center,
                                                                                    int number_of_particles,
                                                                                    float min_position,
                                                                                    float max_position)
    : NBodySequentialWithInputFile(active_repulsion_force,
                                   active_repulsion_min_distance,
                                   passive_repulsion_force,
                                   passive_repulsion_min_distance,
                                   damping_force,
                                   central_force,
                                   center,
                                   number_of_particles,
                                   min_position,
                                   max_position),
      main_result_("Frames per second"),
      main_duration_("Run") {
}

void mila::nbody::sequential::NBodySequentialWithInputFileProfiler::Run(const std::string &input_file) {
  auto start_time = std::chrono::high_resolution_clock::now();
  NBodySequentialWithInputFile::Run(input_file);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  results_.insert(std::pair<std::string, float>("Run", duration_us));
  results_.insert(std::pair<std::string, float>("Interactions per second", mila::utils::GetValuePerSecond((number_of_particles_ * number_of_particles_), duration)));
  results_.insert(std::pair<std::string, float>("Frames per second", mila::utils::GetValuePerSecond(number_of_frames_, duration)));
}

std::string mila::nbody::sequential::NBodySequentialWithInputFileProfiler::main_result() const {
  return main_result_;
}

std::string mila::nbody::sequential::NBodySequentialWithInputFileProfiler::main_duration() const {
  return main_duration_;
}

std::map<std::string, float> mila::nbody::sequential::NBodySequentialWithInputFileProfiler::results() const {
  return results_;
}
