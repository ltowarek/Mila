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
