#include "gtest/gtest.h"
#include "sudoku_solver_parallel.h"

TEST(SudokuSolverParallelTest, DefaultConstructor) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  EXPECT_EQ(solver.platform_id(), 0);
  EXPECT_EQ(solver.device_id(), 0);
}

TEST(SudokuSolverParallelTest, DeviceTypeConstructor) {
  mila::sudokusolver::parallel::SudokuSolver solver_0_0(0, 0);
  EXPECT_EQ(solver_0_0.platform_id(), 0);
  EXPECT_EQ(solver_0_0.device_id(), 0);
  mila::sudokusolver::parallel::SudokuSolver solver_1_0(1, 0);
  EXPECT_EQ(solver_1_0.platform_id(), 1);
  EXPECT_EQ(solver_1_0.device_id(), 0);
  mila::sudokusolver::parallel::SudokuSolver solver_0_1(0, 1);
  EXPECT_EQ(solver_0_1.platform_id(), 0);
  EXPECT_EQ(solver_0_1.device_id(), 1);
}
