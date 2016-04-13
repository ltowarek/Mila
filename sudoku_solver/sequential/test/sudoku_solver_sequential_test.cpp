#include "gtest/gtest.h"
#include "sudoku_solver_sequential.h"

TEST(SudokuSolverTest, FindEmptyCellsEmpty) {
  mila::sudokusolver::sequential::SudokuSolver solver;
  std::vector<int> input = {};
  std::vector<int> expected_output = {};

  std::vector<int> output = solver.FindEmptyCells(input);

  EXPECT_EQ(expected_output.size(), output.size());
}

TEST(SudokuSolverTest, FindEmptyCellsNoEmptyCells) {
  mila::sudokusolver::sequential::SudokuSolver solver;
  std::vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> expected_output = {};

  std::vector<int> output = solver.FindEmptyCells(input);

  EXPECT_EQ(expected_output.size(), output.size());
}

TEST(SudokuSolverTest, FindEmptyCells) {
  mila::sudokusolver::sequential::SudokuSolver solver;
  std::vector<int> input = {1, 2, 0, 4, 0, 0, 7, 8, 0};
  std::vector<int> expected_output = {2, 4, 5, 8};

  std::vector<int> output = solver.FindEmptyCells(input);

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}
