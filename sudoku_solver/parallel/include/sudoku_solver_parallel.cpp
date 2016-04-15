#include "sudoku_solver_parallel.h"

mila::sudokusolver::parallel::SudokuSolver::SudokuSolver(): SudokuSolver(0 ,0) {
}

mila::sudokusolver::parallel::SudokuSolver::SudokuSolver(size_t platform_id, size_t device_id): platform_id_(platform_id), device_id_(device_id){
}

size_t mila::sudokusolver::parallel::SudokuSolver::platform_id() const {
  return platform_id_;
}

size_t mila::sudokusolver::parallel::SudokuSolver::device_id() const {
  return device_id_;
}

clpp::Platform mila::sudokusolver::parallel::SudokuSolver::platform() const {
  return platform_;
}

clpp::Device mila::sudokusolver::parallel::SudokuSolver::device() const {
  return device_;
}

clpp::Context mila::sudokusolver::parallel::SudokuSolver::context() const {
  return context_;
}

clpp::Queue mila::sudokusolver::parallel::SudokuSolver::queue() const {
  return queue_;
}

clpp::Kernel mila::sudokusolver::parallel::SudokuSolver::kernel() const {
  return kernel_;
}

void mila::sudokusolver::parallel::SudokuSolver::Initialize(const std::string& options) {
  const auto platforms = clpp::Platform::get();
  platform_ = platforms.at(platform_id_);

  const auto devices = platform_.getAllDevices();
  device_ = devices.at(device_id_);

  context_ = clpp::Context(device_);
  queue_ = clpp::Queue(context_, device_);

  const auto source_file_name = "sudoku_solver.cl";
  const auto kernel_name = std::string("SudokuSolverDFS");
  auto source_file = mila::utils::ReadFile(source_file_name);
  auto program = clpp::Program(context_, source_file);

  try {
    program.build(device_, options.c_str());
  } catch(const clpp::Error& error) {
    printf("%s\n", program.getBuildLog(device_).c_str());
  }
  kernel_ = clpp::Kernel(program, kernel_name.c_str());
}

std::vector<int> mila::sudokusolver::parallel::SudokuSolver::Run(const std::vector<int> &grid, int n) {
  std::stringstream string_stream;
  string_stream << "-D n=" << n;
  Initialize(string_stream.str());

  auto output = grid;
  auto grids = grid;
  auto number_of_grids = 1;
  auto empty_cells = mila::sudokusolver::utils::FindEmptyCells(grid);
  auto numbers_of_empty_cells_per_grid = std::vector<size_t>{empty_cells.size()};
  auto is_solved = 0;

  auto grids_buffer = clpp::Buffer(context_, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, grids.size() * sizeof(grids.at(0)), grids.data());
  auto number_of_grids_buffer = clpp::Buffer(context_, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(number_of_grids), &number_of_grids);
  auto empty_cells_buffer = clpp::Buffer(context_, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, empty_cells.size() * sizeof(empty_cells.at(0)), empty_cells.data());
  auto numbers_of_empty_cells_per_grid_buffer = clpp::Buffer(context_, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, numbers_of_empty_cells_per_grid.size() * sizeof(numbers_of_empty_cells_per_grid.at(0)), numbers_of_empty_cells_per_grid.data());
  auto output_buffer = clpp::Buffer(context_, CL_MEM_WRITE_ONLY, output.size() * sizeof(output.at(0)));
  auto is_solved_buffer = clpp::Buffer(context_, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(is_solved), &is_solved);

  auto global_work_size = {number_of_grids};

  kernel_.setArgs(grids_buffer, number_of_grids_buffer, empty_cells_buffer, numbers_of_empty_cells_per_grid_buffer, output_buffer, is_solved_buffer);
  queue_.enqueueNDRangeKernel(kernel_, global_work_size).wait();
  queue_.readBuffer(output_buffer, 0, output.size() * sizeof(output.at(0)), output.data());

  return output;
}
