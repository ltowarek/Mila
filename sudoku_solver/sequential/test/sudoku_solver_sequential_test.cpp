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

TEST(SudokuSolverTest, IsValidHorizontallyValid) {
  mila::sudokusolver::sequential::SudokuSolver solver;
  std::vector<int> input = {
      1, 2, 3, 4, 5, 6, 7, 8, 9,
      9, 8, 7, 6, 5, 4, 3, 2, 1,
      0, 1, 2, 3, 4, 5, 6, 7, 8
  };

  EXPECT_EQ(solver.IsValidHorizontally(input, 9, 0), true);
  EXPECT_EQ(solver.IsValidHorizontally(input, 9, 1), true);
  EXPECT_EQ(solver.IsValidHorizontally(input, 9, 2), true);
}

TEST(SudokuSolverTest, IsValidHorizontallyInvalid) {
  mila::sudokusolver::sequential::SudokuSolver solver;
  std::vector<int> input = {
      1, 1, 2, 2, 3, 3, 4, 4, 0,
      1, 1, 2, 3, 4, 5, 6, 7, 8,
      1, 1, 1, 1, 1, 1, 1, 1, 1
  };

  EXPECT_EQ(solver.IsValidHorizontally(input, 9, 0), false);
  EXPECT_EQ(solver.IsValidHorizontally(input, 9, 1), false);
  EXPECT_EQ(solver.IsValidHorizontally(input, 9, 2), false);
}

TEST(SudokuSolverTest, IsValidVericallyValid) {
  mila::sudokusolver::sequential::SudokuSolver solver;
  std::vector<int> input = {
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      2, 2, 2, 1, 1, 1, 1, 1, 1,
      3, 3, 3, 1, 1, 1, 1, 1, 1
  };

  EXPECT_EQ(solver.IsValidVertically(input, 9, 0), true);
  EXPECT_EQ(solver.IsValidVertically(input, 9, 1), true);
  EXPECT_EQ(solver.IsValidVertically(input, 9, 2), true);
}

TEST(SudokuSolverTest, IsValidVericallyInvalid) {
  mila::sudokusolver::sequential::SudokuSolver solver;
  std::vector<int> input = {
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      2, 2, 2, 1, 1, 1, 2, 2, 2,
      3, 3, 3, 1, 1, 1, 3, 3, 3
  };

  EXPECT_EQ(solver.IsValidVertically(input, 9, 3), false);
  EXPECT_EQ(solver.IsValidVertically(input, 9, 4), false);
  EXPECT_EQ(solver.IsValidVertically(input, 9, 5), false);
}
