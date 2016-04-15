#ifndef MILA_SUDOKU_SOLVER_PARALLEL_H_
#define MILA_SUDOKU_SOLVER_PARALLEL_H_

#include "clpp.h"

namespace mila {
namespace sudokusolver {
namespace parallel {

class SudokuSolver {
 public:
  SudokuSolver();
  SudokuSolver(size_t platform_id, size_t device_id);

  size_t platform_id() const;
  size_t device_id() const;
 private:
  const size_t platform_id_;
  const size_t device_id_;
};

}  // parallel
}  // sudokusolver
}  // mila

#endif  // MILA_SUDOKU_SOLVER_PARALLEL_H_
