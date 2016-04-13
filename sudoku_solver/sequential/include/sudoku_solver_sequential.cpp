#include "sudoku_solver_sequential.h"

std::vector<int> mila::sudokusolver::sequential::SudokuSolver::FindEmptyCells(const std::vector<int> &grid) const {
  auto output = std::vector<int>();
  for (auto i = 0; i < grid.size(); ++i) {
    if (grid[i] == 0) {
      output.push_back(i);
    }
  }
  return output;
}
