#ifndef MILA_SUDOKU_SOLVER_SEQUENTIAL_H_
#define MILA_SUDOKU_SOLVER_SEQUENTIAL_H_

#include <algorithm>
#include <vector>

#include "sudoku_solver_utils.h"

namespace mila {
namespace sudokusolver {
namespace sequential {

class SudokuSolver {
 public:
  std::vector<int> FindEmptyCells(const std::vector<int>& grid) const;
  bool IsValidHorizontally(const std::vector<int>& grid, int n, int row) const;
  bool IsValidVertically(const std::vector<int>& grid, int n, int column) const;
  bool IsValidInBoxes(const std::vector<int>& grid, int n, int row, int column) const;
  bool IsValidMove(const std::vector<int>& grid, int n, int field) const;
  virtual std::vector<int> Run(const std::vector<int>& grid, int n);
};

class SudokuSolverBasedOnFiles: public SudokuSolver {
 public:
  virtual std::vector<int> Run(const std::vector<int>& grid, int n) override;
  virtual void Run(const std::string& input_file_name, const std::string& output_file_name);
};

}  // sequential
}  // sudokusolver
}  // mila

#endif  // MILA_SUDOKU_SOLVER_SEQUENTIAL_H_
