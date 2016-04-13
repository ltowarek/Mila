#ifndef MILA_SUDOKU_SOLVER_SEQUENTIAL_PROFILER_H_
#define MILA_SUDOKU_SOLVER_SEQUENTIAL_PROFILER_H_

#include <chrono>
#include <map>

#include "sudoku_solver_sequential.h"

namespace mila {
namespace sudokusolver {
namespace sequential {

class SudokuSolverProfiler: public SudokuSolver {
 public:
  SudokuSolverProfiler();

  std::vector<int> Run(const std::vector<int>& grid, int n) override;

  std::string main_result() const;
  std::map<std::string, int64_t> results() const;
 private:
  const std::string main_result_;
  std::map<std::string, int64_t> results_;
};

class SudokuSolverBasedOnFilesProfiler: public SudokuSolverBasedOnFiles {
 public:
  SudokuSolverBasedOnFilesProfiler();

  std::vector<int> Run(const std::vector<int>& grid, int n) override;
  void Run(const std::string& input_file_name, const std::string& output_file_name) override;

  std::string main_result() const;
  std::map<std::string, int64_t> results() const;
 private:
  const std::string main_result_;
  std::map<std::string, int64_t> results_;
};

}  // sequential
}  // sudokusolver
}  // mila

#endif  // MILA_SUDOKU_SOLVER_SEQUENTIAL_PROFILER_H_
