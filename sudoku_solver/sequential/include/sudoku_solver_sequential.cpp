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

bool mila::sudokusolver::sequential::SudokuSolver::IsValidHorizontally(const std::vector<int> &grid,
                                                                       int n,
                                                                       int row) const {
  auto is_valid = true;
  auto checked_numbers = std::vector<int>();

  for (auto column = 0; column < n; ++column) {
    auto value = grid[row * n + column];
    if (value != 0 && std::find(checked_numbers.begin(), checked_numbers.end(), value) != checked_numbers.end()) {
      is_valid = false;
      break;
    } else {
      checked_numbers.push_back(value);
    }
  }

  return is_valid;
}
