#ifndef MILA_SUDOKU_SOLVER_PARALLEL_H_
#define MILA_SUDOKU_SOLVER_PARALLEL_H_

#include <string>
#include <sstream>

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

  virtual std::vector<int> Run(const std::vector<int>& grid, int n);

  size_t platform_id() const;
  size_t device_id() const;
  clpp::Platform platform() const;
  clpp::Device device() const;
  clpp::Context context() const;
  clpp::Queue queue() const;
  clpp::Kernel kernel() const;
 protected:
  virtual void Initialize(const std::string& options);

  const size_t platform_id_;
  const size_t device_id_;
  clpp::Platform platform_;
  clpp::Device device_;
  clpp::Context context_;
  clpp::Queue queue_;
  clpp::Kernel kernel_;
};

}  // parallel
}  // sudokusolver
}  // mila

#endif  // MILA_SUDOKU_SOLVER_PARALLEL_H_
