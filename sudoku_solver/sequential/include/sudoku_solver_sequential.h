#ifndef MILA_SUDOKU_SOLVER_SEQUENTIAL_H_
#define MILA_SUDOKU_SOLVER_SEQUENTIAL_H_

#include <algorithm>
#include <vector>

namespace mila {
namespace sudokusolver {
namespace sequential {

class SudokuSolver {
 public:
  std::vector<int> FindEmptyCells(const std::vector<int>& grid) const;
  bool IsValidHorizontally(const std::vector<int>& grid, int n, int row) const;
};

}  // sequential
}  // sudokusolver
}  // mila

#endif  // MILA_SUDOKU_SOLVER_SEQUENTIAL_H_
