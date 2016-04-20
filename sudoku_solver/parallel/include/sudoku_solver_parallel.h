#ifndef MILA_SUDOKU_SOLVER_PARALLEL_H_
#define MILA_SUDOKU_SOLVER_PARALLEL_H_

#include <string>
#include <sstream>
#include <tuple>

#include "clpp.h"

#include "sudoku_solver_utils.h"
#include "utils.h"

namespace mila {
namespace sudokusolver {
namespace parallel {

class SudokuSolver {
 public:
  SudokuSolver();
  SudokuSolver(size_t platform_id, size_t device_id);

  virtual std::vector<int> Run(const std::vector<int>& grid, int number_of_cells_to_fill);
  virtual std::tuple<std::vector<int>, int, std::vector<int>, std::vector<int>> GeneratePossibleSolutions(const std::vector<int>& grid, int number_of_cells_to_fill);
  virtual std::vector<int> SolveSudoku(std::vector<int>& grids, int number_of_grids, std::vector<int>& empty_cells, std::vector<int>& numbers_of_empty_cells_per_grid);

  uint32_t n() const;
  size_t platform_id() const;
  size_t device_id() const;
  clpp::Platform platform() const;
  clpp::Device device() const;
  clpp::Context context() const;
  clpp::Queue queue() const;
  clpp::Kernel dfs_kernel() const;
  clpp::Kernel bfs_kernel() const;
 protected:
  virtual void Initialize(const std::string& options);

  const uint32_t n_;
  const size_t platform_id_;
  const size_t device_id_;
  const int max_number_of_grids_;
  const int max_number_of_cells_;
  clpp::Platform platform_;
  clpp::Device device_;
  clpp::Context context_;
  clpp::Queue queue_;
  clpp::Kernel dfs_kernel_;
  clpp::Kernel bfs_kernel_;
  bool is_initialized_;
};

class SudokuSolverBasedOnFiles: public SudokuSolver {
 public:
  SudokuSolverBasedOnFiles();
  SudokuSolverBasedOnFiles(size_t platform_id, size_t device_id);

  virtual std::vector<int> Run(const std::vector<int>& grid, int number_of_cells_to_fill) override;
  virtual void Run(const std::string& input_file_name, const std::string& output_file_name, int number_of_cells_to_fill);
};

}  // parallel
}  // sudokusolver
}  // mila

#endif  // MILA_SUDOKU_SOLVER_PARALLEL_H_
