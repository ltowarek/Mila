#ifndef MILA_SUDOKU_SOLVER_PARALLEL_PROFILER_H_
#define MILA_SUDOKU_SOLVER_PARALLEL_PROFILER_H_

#include <chrono>
#include <map>

#include "sudoku_solver_parallel.h"

namespace mila {
namespace sudokusolver {
namespace parallel {

class SudokuSolverProfiler: public SudokuSolver {
 public:
  SudokuSolverProfiler();
  SudokuSolverProfiler(size_t platform_id, size_t device_id);

  std::vector<int> Run(const std::vector<int>& grid, int number_of_cells_to_fill) override;

  std::string main_result() const;
  std::map<std::string, int64_t> results() const;
 private:
  const std::string main_result_;
  std::map<std::string, int64_t> results_;
};

}  // parallel
}  // sudokusolver
}  // mila

#endif  // MILA_SUDOKU_SOLVER_PARALLEL_PROFILER_H_
