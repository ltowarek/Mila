#include "sudoku_solver_parallel_profiler.h"

mila::sudokusolver::parallel::SudokuSolverProfiler::SudokuSolverProfiler(): SudokuSolverProfiler(0, 0) {
}

mila::sudokusolver::parallel::SudokuSolverProfiler::SudokuSolverProfiler(size_t platform_id, size_t device_id): SudokuSolver(platform_id, device_id), main_result_("Run") {
}

std::vector<int> mila::sudokusolver::parallel::SudokuSolverProfiler::Run(const std::vector<int> &grid,
                                                                         int number_of_cells_to_fill) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = SudokuSolver::Run(grid, number_of_cells_to_fill);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("Run", duration));
  return output;
}

std::tuple<std::vector<int>,
           int,
           std::vector<int>,
           std::vector<int>> mila::sudokusolver::parallel::SudokuSolverProfiler::GeneratePossibleSolutions(const std::vector<
    int> &grid, int number_of_cells_to_fill) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = SudokuSolver::GeneratePossibleSolutions(grid, number_of_cells_to_fill);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("GeneratePossibleSolutions", duration));
  return output;
}

std::vector<int> mila::sudokusolver::parallel::SudokuSolverProfiler::SolveSudoku(std::vector<int> &grids,
                                                                                 int number_of_grids,
                                                                                 std::vector<int> &empty_cells,
                                                                                 std::vector<int> &numbers_of_empty_cells_per_grid) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = SudokuSolver::SolveSudoku(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("SolveSudoku", duration));
  return output;
}

std::string mila::sudokusolver::parallel::SudokuSolverProfiler::main_result() const {
  return main_result_;
}

std::map<std::string, int64_t> mila::sudokusolver::parallel::SudokuSolverProfiler::results() const {
  return results_;
}

mila::sudokusolver::parallel::SudokuSolverBasedOnFilesProfiler::SudokuSolverBasedOnFilesProfiler(): SudokuSolverBasedOnFilesProfiler(0, 0) {
}

mila::sudokusolver::parallel::SudokuSolverBasedOnFilesProfiler::SudokuSolverBasedOnFilesProfiler(size_t platform_id,
                                                                                                 size_t device_id): SudokuSolverBasedOnFiles(platform_id, device_id), main_result_("RunWithFiles") {
}

std::vector<int> mila::sudokusolver::parallel::SudokuSolverBasedOnFilesProfiler::Run(const std::vector<int> &grid,
                                                                                     int number_of_cells_to_fill) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = SudokuSolverBasedOnFiles::Run(grid, number_of_cells_to_fill);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("RunWithoutFiles", duration));
  return output;
}

void mila::sudokusolver::parallel::SudokuSolverBasedOnFilesProfiler::Run(const std::string &input_file_name,
                                                                         const std::string &output_file_name,
                                                                         int number_of_cells_to_fill) {
  auto start_time = std::chrono::high_resolution_clock::now();
  SudokuSolverBasedOnFiles::Run(input_file_name, output_file_name, number_of_cells_to_fill);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("RunWithFiles", duration));
}

std::tuple<std::vector<int>,
           int,
           std::vector<int>,
           std::vector<int>> mila::sudokusolver::parallel::SudokuSolverBasedOnFilesProfiler::GeneratePossibleSolutions(
    const std::vector<int> &grid,
    int number_of_cells_to_fill) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = SudokuSolver::GeneratePossibleSolutions(grid, number_of_cells_to_fill);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("GeneratePossibleSolutions", duration));
  return output;
}

std::vector<int> mila::sudokusolver::parallel::SudokuSolverBasedOnFilesProfiler::SolveSudoku(std::vector<int> &grids,
                                                                                             int number_of_grids,
                                                                                             std::vector<int> &empty_cells,
                                                                                             std::vector<int> &numbers_of_empty_cells_per_grid) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = SudokuSolver::SolveSudoku(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("SolveSudoku", duration));
  return output;
}

std::string mila::sudokusolver::parallel::SudokuSolverBasedOnFilesProfiler::main_result() const {
  return main_result_;
}

std::map<std::string, int64_t> mila::sudokusolver::parallel::SudokuSolverBasedOnFilesProfiler::results() const {
  return results_;
}

