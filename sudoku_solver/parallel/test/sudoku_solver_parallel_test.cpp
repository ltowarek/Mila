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

TEST(SudokuSolverParallelTest, RunSuccess) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  std::vector<int> input {
      0, 0, 0, 0, 3, 7, 6, 0, 0,
      0, 0, 0, 6, 0, 0, 0, 9, 0,
      0, 0, 8, 0, 0, 0, 0, 0, 4,
      0, 9, 0, 0, 0, 0, 0, 0, 1,
      6, 0, 0, 0, 0, 0, 0, 0, 9,
      3, 0, 0, 0, 0, 0, 0, 4, 0,
      7, 0, 0, 0, 0, 0, 8, 0, 0,
      0, 1, 0, 0, 0, 9, 0, 0, 0,
      0, 0, 2, 5, 4, 0, 0, 0, 0
  };
  std::vector<int> expected_output {
      9, 5, 4, 1, 3, 7, 6, 8, 2,
      2, 7, 3, 6, 8, 4, 1, 9, 5,
      1, 6, 8, 2, 9, 5, 7, 3, 4,
      4, 9, 5, 7, 2, 8, 3, 6, 1,
      6, 8, 1, 4, 5, 3, 2, 7, 9,
      3, 2, 7, 9, 6, 1, 5, 4, 8,
      7, 4, 9, 3, 1, 2, 8, 5, 6,
      5, 1, 6, 8, 7, 9, 4, 2, 3,
      8, 3, 2, 5, 4, 6, 9, 1, 7
  };

  std::vector<int> output = solver.Run(input, 9);

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverParallelTest, RunFailure) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  std::vector<int> input = {
      0, 5, 4, 10, 3, 7, 2, 8, 2,
      2, 7, 3, 6, 8, 4, 1, 9, 5,
      1, 6, 8, 2, 9, 5, 7, 3, 4,
      4, 9, 5, 7, 2, 8, 3, 6, 1,
      6, 8, 1, 4, 5, 3, 2, 7, 9,
      3, 2, 7, 9, 6, 1, 5, 4, 8,
      7, 4, 9, 3, 1, 2, 8, 5, 6,
      5, 1, 6, 8, 7, 9, 4, 2, 3,
      8, 3, 2, 5, 4, 6, 9, 1, 7
  };

  std::vector<int> output = solver.Run(input, 9);

  EXPECT_TRUE(std::find(output.begin(), output.end(), 0) != output.end());
}
