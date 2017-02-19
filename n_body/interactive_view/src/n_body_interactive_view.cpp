#include "n_body_interactive_view.hpp"

mila::GenericNBodyInteractiveView::GenericNBodyInteractiveView(std::unique_ptr<mila::NBody> n_body,
                                                               const std::shared_ptr<mila::Logger> logger)
    : n_body_(std::move(n_body)), logger_(logger) {
}

mila::GenericNBodyInteractiveView::GenericNBodyInteractiveView(mila::GenericNBodyInteractiveView &&view)
    : n_body_(std::move(view.n_body_)), logger_(view.logger_) {
}

mila::GenericNBodyInteractiveView::~GenericNBodyInteractiveView() {
}

void mila::GenericNBodyInteractiveView::Record(const mila::NBodyParameters &parameters,
                                               const int number_of_frames,
                                               mila::Vector2DFile &mouse_positions_file,
                                               mila::Vector2DFile &output_particles_file,
                                               std::vector<mila::Particle> &particles) {
  const auto width = static_cast<int>(parameters.center.x * 2);
  const auto height = static_cast<int>(parameters.center.y * 2);
  const auto title = std::string("N-Body");

  mouse_positions_file.Remove();
  output_particles_file.Remove();

  if (!glfwInit()) {
    logger_->Critical("Failed to initialize OpenGL");
    return;
  }

  const auto window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window) {
    logger_->Critical("Failed to create window");
    return;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);

  // Intentional infinite loop when number_of_frames is negative
  for (auto frame = number_of_frames; frame != 0 && !glfwWindowShouldClose(window); --frame) {
    const auto mouse_position = GetMousePosition(window);
    mouse_positions_file.Write(mouse_position);
    n_body_->UpdateParticles(parameters, mouse_position, particles);
    DrawParticles(width, height, particles);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();

  auto positions = std::vector<Vector2D>();
  for (const auto particle : particles) {
    positions.push_back(particle.position);
  }
  output_particles_file.Write(positions);
}

bool mila::GenericNBodyInteractiveView::Replay(const mila::NBodyParameters &parameters,
                                               const mila::Vector2DFile &mouse_positions_file,
                                               const mila::Vector2DFile &reference_particles_file,
                                               std::vector<mila::Particle> &particles) {
  const auto width = static_cast<int>(parameters.center.x * 2);
  const auto height = static_cast<int>(parameters.center.y * 2);
  const auto title = std::string("N-Body");

  const auto mouse_positions = mouse_positions_file.Read();
  const auto number_of_frames = mouse_positions.size();

  if (!glfwInit()) {
    logger_->Critical("Failed to initialize OpenGL");
    return false;
  }

  const auto window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window) {
    logger_->Critical("Failed to create window");
    return false;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);

  for (auto frame = 0; frame < number_of_frames && !glfwWindowShouldClose(window); ++frame) {
    const auto mouse_position = mouse_positions[frame];
    n_body_->UpdateParticles(parameters, mouse_position, particles);
    DrawParticles(width, height, particles);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  auto output = std::vector<mila::Vector2D>();
  std::transform(particles.begin(),
                 particles.end(),
                 std::back_inserter(output),
                 [](mila::Particle const &p) { return p.position; });
  const auto reference = reference_particles_file.Read();

  if (output.size() != reference.size()) {
    logger_->Error("Output size is not equal to reference size: %llu vs %llu", output.size(), reference.size());
    return false;
  }

  for (auto i = 0; i < output.size(); ++i) {
    if (!mila::Vector2D::AreEqual(output[i], reference[i], 1e+1)) {
      logger_->Error("Output is not equal to reference: [%f,%f] vs [%f,%f] at particle: %llu",
                     output[i].x,
                     output[i].y,
                     reference[i].x,
                     reference[i].y,
                     i);
      return false;
    }
  }

  logger_->Info("Output is equal to reference");
  return true;
}

void mila::GenericNBodyInteractiveView::DrawParticles(const int width,
                                                      const int height,
                                                      const std::vector<mila::Particle> &particles) const {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, height, 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  for (auto i = 0; i < particles.size(); ++i) {
    glPointSize(1.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(particles[i].position.x, particles[i].position.y);
    glEnd();
  }
}

mila::Vector2D mila::GenericNBodyInteractiveView::GetMousePosition(GLFWwindow *window) const {
  auto mouse_x = 0.0;
  auto mouse_y = 0.0;
  glfwGetCursorPos(window, &mouse_x, &mouse_y);
  return mila::Vector2D{static_cast<float>(mouse_x), static_cast<float>(mouse_y)};
}

mila::Vector2DFile::Vector2DFile(const std::string &file_name) : file_name_(file_name) {
}

void mila::Vector2DFile::Write(const mila::Vector2D &vector) {
  auto file_stream = std::ofstream(file_name_, std::ofstream::app);
  file_stream << vector.x << "," << vector.y << "\n";
}

void mila::Vector2DFile::Write(const std::vector<mila::Vector2D> &vectors) {
  auto file_stream = std::ofstream(file_name_, std::ofstream::app);
  for (const auto vector : vectors) {
    file_stream << vector.x << "," << vector.y << "\n";
  }
}

bool mila::Vector2DFile::IsValid() const {
  return std::ifstream(file_name_).good();
}

void mila::Vector2DFile::Remove() const {
  std::remove(file_name_.c_str());
}

std::vector<mila::Vector2D> mila::Vector2DFile::Read() const {
  auto output = std::vector<Vector2D>();
  auto file_stream = std::ifstream(file_name_);
  auto position = Vector2D();
  auto comma = char{};
  while (file_stream >> position.x >> comma >> position.y) {
    output.push_back(position);
  }
  return output;
}

mila::NBodyInteractiveViewStub::~NBodyInteractiveViewStub() {

}

void mila::NBodyInteractiveViewStub::Record(const mila::NBodyParameters &parameters,
                                            const int number_of_frames,
                                            mila::Vector2DFile &mouse_positions_file,
                                            mila::Vector2DFile &output_particles_file,
                                            std::vector<mila::Particle> &particles) {
}

bool mila::NBodyInteractiveViewStub::Replay(const mila::NBodyParameters &parameters,
                                            const mila::Vector2DFile &mouse_positions_file,
                                            const mila::Vector2DFile &reference_particles_file,
                                            std::vector<mila::Particle> &particles) {
  return true;
}
