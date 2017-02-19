#include "gtest/gtest.h"
#include "n_body_sequential.hpp"
#include "n_body_interactive_view.hpp"
#include "n_body_interactive_view_profiler.hpp"
#include "n_body_interactive_view_app.hpp"

TEST(NBodyInteractiveViewTest, Record) {
  const auto logger_spy = std::shared_ptr<mila::LoggerSpy>(new mila::LoggerSpy());
  auto n_body = std::unique_ptr<mila::NBody>(new mila::SequentialNBody(logger_spy));
  auto n_body_view = mila::GenericNBodyInteractiveView(std::move(n_body), logger_spy);
  auto particles = std::vector<mila::Particle>{
      {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}},
      {{10.0f, 20.0f}, {30.0f, 40.0f}, {50.0f, 60.0f}}
  };
  const auto parameters = mila::NBodyParameters();
  auto mouse_positions_file = mila::Vector2DFile("mouse_positions.txt");
  auto output_particles_file = mila::Vector2DFile("output_particles.txt");
  const int number_of_frames = 2;
  n_body_view.Record(parameters, number_of_frames, mouse_positions_file, output_particles_file, particles);
  EXPECT_TRUE(mouse_positions_file.IsValid());
  EXPECT_TRUE(output_particles_file.IsValid());
  mouse_positions_file.Remove();
  output_particles_file.Remove();
}

TEST(NBodyInteractiveViewTest, Replay) {
  const auto logger_spy = std::shared_ptr<mila::LoggerSpy>(new mila::LoggerSpy());
  auto n_body = std::unique_ptr<mila::NBody>(new mila::SequentialNBody(logger_spy));
  auto n_body_view = mila::GenericNBodyInteractiveView(std::move(n_body), logger_spy);
  auto particles = std::vector<mila::Particle>{
      {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}},
      {{10.0f, 20.0f}, {30.0f, 40.0f}, {50.0f, 60.0f}}
  };
  const auto parameters = mila::NBodyParameters();
  const auto mouse_positions_file = mila::Vector2DFile("reference_mouse_positions.txt");
  const auto reference_particles_file = mila::Vector2DFile("reference_particles.txt");
  EXPECT_TRUE(n_body_view.Replay(parameters, mouse_positions_file, reference_particles_file, particles));
}

TEST(NBodyInteractiveViewProfilerTest, GetResultsAfterReplay) {
  auto profiler = std::unique_ptr<mila::Profiler>(new mila::ProfilerStub());
  auto n_body = std::unique_ptr<mila::NBodyInteractiveView>(new mila::NBodyInteractiveViewStub());
  auto n_body_profiler = mila::NBodyInteractiveViewProfiler(std::move(n_body), std::move(profiler), nullptr);
  auto particles = std::vector<mila::Particle>{
      {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}},
      {{10.0f, 20.0f}, {30.0f, 40.0f}, {50.0f, 60.0f}}
  };
  const auto parameters = mila::NBodyParameters();
  const auto mouse_positions_file = mila::Vector2DFile("reference_mouse_positions.txt");
  const auto reference_particles_file = mila::Vector2DFile("reference_particles.txt");

  n_body_profiler.Replay(parameters, mouse_positions_file, reference_particles_file, particles);
  EXPECT_GT(n_body_profiler.GetResults().frames_per_second, 0.0f);
  EXPECT_GT(n_body_profiler.GetResults().replay_duration.count(), 0);
}

TEST(ParallelNBodyInteractiveViewAppTest, Run_Replay) {
  const auto logger_spy = std::shared_ptr<mila::LoggerSpy>(new mila::LoggerSpy());
  const auto number_of_particles = std::string("10");
  const auto mouse_positions = std::string("reference_mouse_positions.txt");
  const auto reference_particles = std::string("reference_particles.txt");
  const auto platform_id = std::string("0");
  const auto device_id = std::string("0");
  const auto number_of_iterations = std::string("2");
  const char *parameters[] =
      {"app", "replay", number_of_particles.c_str(), mouse_positions.c_str(), reference_particles.c_str(),
       platform_id.c_str(), device_id.c_str(), number_of_iterations.c_str()};
  const auto n_body = mila::ParallelNBodyInteractiveViewApp(logger_spy);
  // const_cast due to C vs C++ string literals
  n_body.Run(8, const_cast<char **>(parameters));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mouse positions file: " + mouse_positions));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Particles file: " + reference_particles));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Platform id: " + platform_id));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Device id: " + device_id));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of iterations: " + number_of_iterations));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Replay duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Replay duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Replay duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Replay duration coefficient of variation: "));
}

TEST(SequentialNBodyInteractiveViewAppTest, Run_Replay) {
  const auto logger_spy = std::shared_ptr<mila::LoggerSpy>(new mila::LoggerSpy());
  const auto number_of_particles = std::string("10");
  const auto mouse_positions = std::string("reference_mouse_positions.txt");
  const auto reference_particles = std::string("reference_particles.txt");
  const auto number_of_iterations = std::string("2");
  const char *parameters[] =
      {"app", "replay", number_of_particles.c_str(), mouse_positions.c_str(), reference_particles.c_str(),
       number_of_iterations.c_str()};
  const auto n_body = mila::SequentialNBodyInteractiveViewApp(logger_spy);
  // const_cast due to C vs C++ string literals
  n_body.Run(6, const_cast<char **>(parameters));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Mouse positions file: " + mouse_positions));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Particles file: " + reference_particles));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Number of iterations: " + number_of_iterations));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Throughput coefficient of variation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Replay duration mean: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Replay duration median: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Replay duration standard deviation: "));
  EXPECT_TRUE(mila::ContainsStr(mila::logger_spy_messages, "I Replay duration coefficient of variation: "));
}
