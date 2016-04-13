#include "sudoku_solver_sequential_profiler.h"

mila::sudokusolver::sequential::SudokuSolverProfiler::SudokuSolverProfiler(): main_result_("Run") {}

std::string mila::sudokusolver::sequential::SudokuSolverProfiler::main_result() const {
  return main_result_;
}

std::map<std::string, int64_t> mila::sudokusolver::sequential::SudokuSolverProfiler::results() const {
  return results_;
}

std::vector<int> mila::sudokusolver::sequential::SudokuSolverProfiler::Run(const std::vector<int> &grid, int n) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = SudokuSolver::Run(grid, n);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("Run", duration));
  return output;
}
