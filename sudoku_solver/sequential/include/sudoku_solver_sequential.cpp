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

bool mila::sudokusolver::sequential::SudokuSolver::IsValidVertically(const std::vector<int> &grid,
                                                                    int n,
                                                                    int column) const {
  auto is_valid = true;
  auto checked_numbers = std::vector<int>();

  for (auto row = 0; row < n; ++row) {
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

bool mila::sudokusolver::sequential::SudokuSolver::IsValidInBoxes(const std::vector<int> &grid,
                                                                  int n,
                                                                  int row,
                                                                  int column) const {
  const auto box_size = int(sqrt(n));
  const auto box_row = row / box_size;
  const auto box_column = column / box_size;
  auto is_valid = true;
  auto checked_numbers = std::vector<int>();

  for (auto tmp_row = box_row * box_size; tmp_row < box_row * box_size + box_size; ++tmp_row) {
    for (auto tmp_column = box_column * box_size; tmp_column < box_column * box_size + box_size; ++tmp_column) {
      auto value = grid[tmp_row * n + tmp_column];
      if (value != 0 && std::find(checked_numbers.begin(), checked_numbers.end(), value) != checked_numbers.end()) {
        is_valid = false;
        break;
      } else {
        checked_numbers.push_back(value);
      }
    }
  }

  return is_valid;
}

bool mila::sudokusolver::sequential::SudokuSolver::IsValidMove(const std::vector<int> &grid, int n, int field) const {
  const auto row = field / n;
  const auto column = field % n;
  return grid[field] >= 1 &&
      grid[field] <= n &&
      IsValidHorizontally(grid, n, row) &&
      IsValidVertically(grid, n, column) &&
      IsValidInBoxes(grid, n, row, column);
}
