#include "sudoku_solver_parallel.h"

mila::sudokusolver::parallel::SudokuSolver::SudokuSolver(): SudokuSolver(0 ,0) {
}

mila::sudokusolver::parallel::SudokuSolver::SudokuSolver(size_t platform_id, size_t device_id): platform_id_(platform_id),
                                                                                                device_id_(device_id),
                                                                                                number_of_threads_(256),
                                                                                                n_(9),
                                                                                                max_number_of_grids_(5000),
                                                                                                max_number_of_cells_(max_number_of_grids_ * n_* n_),
                                                                                                is_initialized_(false) {
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

clpp::Kernel mila::sudokusolver::parallel::SudokuSolver::dfs_kernel() const {
  return dfs_kernel_;
}

clpp::Kernel mila::sudokusolver::parallel::SudokuSolver::bfs_kernel() const {
  return bfs_kernel_;
}

uint32_t mila::sudokusolver::parallel::SudokuSolver::n() const {
  return n_;
}

void mila::sudokusolver::parallel::SudokuSolver::Initialize(const std::string& options) {
  if (is_initialized_) {
    return;
  }

  const auto platforms = clpp::Platform::get();
  platform_ = platforms.at(platform_id_);

  const auto devices = platform_.getAllDevices();
  device_ = devices.at(device_id_);

  context_ = clpp::Context(device_);
  queue_ = clpp::Queue(context_, device_);

  const auto source_file_name = "sudoku_solver.cl";
  const auto kernel_name = std::string("SudokuSolverDFS");
  const auto bfs_kernel_name = std::string("SudokuSolverBFS");
  auto source_file = mila::utils::ReadFile(source_file_name);
  auto program = clpp::Program(context_, source_file);

  try {
    program.build(device_, options.c_str());
  } catch(const clpp::Error& error) {
    printf("%s\n", program.getBuildLog(device_).c_str());
  }
  dfs_kernel_ = clpp::Kernel(program, kernel_name.c_str());
  bfs_kernel_ = clpp::Kernel(program, bfs_kernel_name.c_str());

  is_initialized_ = true;
}

std::vector<int> mila::sudokusolver::parallel::SudokuSolver::Run(const std::vector<int> &grid, int number_of_cells_to_fill) {
  auto grids = std::vector<int>{};
  auto number_of_grids = int{0};
  auto empty_cells = std::vector<int>{};
  auto numbers_of_empty_cells_per_grid = std::vector<int>{};

  std::tie(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid) = GeneratePossibleSolutions(grid, number_of_cells_to_fill);

  auto output = SolveSudoku(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid);

  return output;
}

std::tuple<std::vector<int>,
           int,
           std::vector<int>,
           std::vector<int>> mila::sudokusolver::parallel::SudokuSolver::GeneratePossibleSolutions(const std::vector<int> &grid,
                                                                                                   int number_of_cells_to_fill) {
  std::stringstream string_stream;
  string_stream << "-D n=" << n_;
  Initialize(string_stream.str());

  std::vector<int> grids = std::vector<int>(max_number_of_cells_, 0);
  std::copy(grid.begin(), grid.end(), grids.begin());

  auto empty_cells = std::vector<int>(max_number_of_cells_, 0);
  auto numbers_of_empty_cells_per_grid = std::vector<int>(max_number_of_grids_, 0);

  auto old_grids_buffer = clpp::Buffer(context_, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, grids.size() * sizeof(grids.at(0)), grids.data());
  auto number_of_old_grids = 1;
  auto number_of_old_grids_buffer = clpp::Buffer(context_, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(number_of_old_grids), &number_of_old_grids);

  auto new_grids_buffer = clpp::Buffer(context_, CL_MEM_WRITE_ONLY, grids.size() * sizeof(grids.at(0)), nullptr);
  auto number_of_new_grids = 0;
  auto number_of_new_grids_buffer = clpp::Buffer(context_, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(number_of_new_grids), &number_of_new_grids);

  auto empty_cells_buffer = clpp::Buffer(context_, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, empty_cells.size() * sizeof(empty_cells.at(0)), empty_cells.data());
  auto numbers_of_empty_cells_per_grid_buffer = clpp::Buffer(context_, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, numbers_of_empty_cells_per_grid.size() * sizeof(numbers_of_empty_cells_per_grid.at(0)), numbers_of_empty_cells_per_grid.data());

  auto global_work_size = std::vector<int>{number_of_threads_};

  for (auto i = 0; i < number_of_cells_to_fill; ++i) {
    // TODO: Replace with fillBuffer from ocl1.2
    auto mapped_buffer = static_cast<int*>(queue_.mapBuffer(empty_cells_buffer, CL_MAP_WRITE, 0, empty_cells.size() * sizeof(empty_cells.at(0))));
    for (auto j = 0; j < empty_cells.size(); ++j) {
      mapped_buffer[j] = 0;
    }
    queue_.enqueueUnmapMemObject(empty_cells_buffer, mapped_buffer).wait();

    bfs_kernel_.setArgs(old_grids_buffer, number_of_old_grids_buffer, new_grids_buffer, number_of_new_grids_buffer, empty_cells_buffer, numbers_of_empty_cells_per_grid_buffer);
    queue_.enqueueNDRangeKernel(bfs_kernel_, global_work_size).wait();
    queue_.enqueueCopyBuffer(new_grids_buffer, old_grids_buffer, 0, 0, grids.size() * sizeof(grids.at(0))).wait();
    queue_.enqueueCopyBuffer(number_of_new_grids_buffer, number_of_old_grids_buffer, 0, 0, sizeof(number_of_new_grids)).wait();

    // TODO: Replace with fillBuffer from ocl1.2
    mapped_buffer = static_cast<int*>(queue_.mapBuffer(number_of_new_grids_buffer, CL_MAP_WRITE, 0, sizeof(number_of_new_grids)));
    *mapped_buffer = 0;
    queue_.enqueueUnmapMemObject(number_of_new_grids_buffer, mapped_buffer).wait();
  }

  // TODO: Buffers can be shared within an object so readBuffer won't be needed
  queue_.readBuffer(old_grids_buffer, 0, grids.size() * sizeof(grids.at(0)), grids.data());
  queue_.readBuffer(number_of_old_grids_buffer, 0, sizeof(number_of_old_grids), &number_of_old_grids);
  queue_.readBuffer(empty_cells_buffer, 0, empty_cells.size() * sizeof(empty_cells.at(0)), empty_cells.data());
  queue_.readBuffer(numbers_of_empty_cells_per_grid_buffer, 0, numbers_of_empty_cells_per_grid.size() * sizeof(numbers_of_empty_cells_per_grid.at(0)), numbers_of_empty_cells_per_grid.data());

  return std::tuple<std::vector<int>, int, std::vector<int>, std::vector<int>>(grids, number_of_old_grids, empty_cells, numbers_of_empty_cells_per_grid);
}

std::vector<int> mila::sudokusolver::parallel::SudokuSolver::SolveSudoku(std::vector<int> &grids,
                                                                         int number_of_grids,
                                                                         std::vector<int> &empty_cells,
                                                                         std::vector<int> &numbers_of_empty_cells_per_grid) {
  std::stringstream string_stream;
  string_stream << "-D n=" << n_;
  Initialize(string_stream.str());

  auto output = std::vector<int>(n_ * n_, 0);
  auto is_solved = int{0};

  auto grids_buffer = clpp::Buffer(context_, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, grids.size() * sizeof(grids.at(0)), grids.data());
  auto number_of_grids_buffer = clpp::Buffer(context_, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(number_of_grids), &number_of_grids);
  auto empty_cells_buffer = clpp::Buffer(context_, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, empty_cells.size() * sizeof(empty_cells.at(0)), empty_cells.data());
  auto numbers_of_empty_cells_per_grid_buffer = clpp::Buffer(context_, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, numbers_of_empty_cells_per_grid.size() * sizeof(numbers_of_empty_cells_per_grid.at(0)), numbers_of_empty_cells_per_grid.data());
  auto output_buffer = clpp::Buffer(context_, CL_MEM_WRITE_ONLY, output.size() * sizeof(output.at(0)));
  auto is_solved_buffer = clpp::Buffer(context_, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(is_solved), &is_solved);

  auto global_work_size = {number_of_threads_};

  dfs_kernel_.setArgs(grids_buffer, number_of_grids_buffer, empty_cells_buffer, numbers_of_empty_cells_per_grid_buffer, output_buffer, is_solved_buffer);
  queue_.enqueueNDRangeKernel(dfs_kernel_, global_work_size).wait();
  queue_.readBuffer(output_buffer, 0, output.size() * sizeof(output.at(0)), output.data());

  return output;
}

mila::sudokusolver::parallel::SudokuSolverBasedOnFiles::SudokuSolverBasedOnFiles(): SudokuSolverBasedOnFiles(0, 0) {
}

mila::sudokusolver::parallel::SudokuSolverBasedOnFiles::SudokuSolverBasedOnFiles(size_t platform_id, size_t device_id): SudokuSolver(platform_id, device_id) {
}

std::vector<int> mila::sudokusolver::parallel::SudokuSolverBasedOnFiles::Run(const std::vector<int> &grid,
                                                                             int number_of_cells_to_fill) {
  return SudokuSolver::Run(grid, number_of_cells_to_fill);
}

void mila::sudokusolver::parallel::SudokuSolverBasedOnFiles::Run(const std::string &input_file_name,
                                                                 const std::string &output_file_name,
                                                                 int number_of_cells_to_fill) {
  auto input_file = mila::sudokusolver::utils::SudokuFile(input_file_name);
  auto output_file = mila::sudokusolver::utils::SudokuFile(output_file_name);

  auto input_grid = input_file.Read();
  auto output_grid = Run(input_grid, number_of_cells_to_fill);

  output_file.Write(output_grid);
}
