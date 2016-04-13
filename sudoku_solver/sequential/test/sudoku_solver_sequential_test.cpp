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

TEST(SudokuSolverTest, IsValidVerticallyValid) {
  mila::sudokusolver::sequential::SudokuSolver solver;
  std::vector<int> input = {
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      2, 2, 2, 1, 1, 2, 2, 2, 2,
      3, 3, 3, 1, 3, 3, 3, 3, 3,
      4, 4, 4, 1, 4, 4, 4, 4, 4,
      5, 5, 5, 1, 5, 5, 5, 5, 5,
      6, 6, 6, 1, 6, 6, 6, 6, 6,
      7, 7, 7, 1, 7, 7, 7, 7, 7,
      8, 8, 8, 1, 8, 8, 8, 8, 8,
      9, 9, 9, 1, 9, 1, 9, 9, 9
  };

  EXPECT_EQ(solver.IsValidVertically(input, 9, 0), true);
  EXPECT_EQ(solver.IsValidVertically(input, 9, 1), true);
  EXPECT_EQ(solver.IsValidVertically(input, 9, 2), true);
}

TEST(SudokuSolverTest, IsValidVerticallyInvalid) {
  mila::sudokusolver::sequential::SudokuSolver solver;
  std::vector<int> input = {
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      2, 2, 2, 1, 1, 2, 2, 2, 2,
      3, 3, 3, 1, 3, 3, 3, 3, 3,
      4, 4, 4, 1, 4, 4, 4, 4, 4,
      5, 5, 5, 1, 5, 5, 5, 5, 5,
      6, 6, 6, 1, 6, 6, 6, 6, 6,
      7, 7, 7, 1, 7, 7, 7, 7, 7,
      8, 8, 8, 1, 8, 8, 8, 8, 8,
      9, 9, 9, 1, 9, 1, 9, 9, 9
  };

  EXPECT_EQ(solver.IsValidVertically(input, 9, 3), false);
  EXPECT_EQ(solver.IsValidVertically(input, 9, 4), false);
  EXPECT_EQ(solver.IsValidVertically(input, 9, 5), false);
}

TEST(SudokuSolverTest, IsValidInBoxesValid) {
  mila::sudokusolver::sequential::SudokuSolver solver;
  std::vector<int> input = {
      1, 2, 3, 1, 1, 1, 1, 1, 1,
      4, 5, 6, 1, 1, 1, 2, 2, 2,
      7, 8, 9, 1, 1, 1, 3, 3, 3,
      4, 4, 4, 9, 8, 7, 4, 4, 4,
      5, 5, 5, 6, 5, 4, 5, 5, 5,
      6, 6, 6, 3, 2, 1, 6, 6, 6,
      7, 7, 7, 1, 2, 3, 1, 4, 7,
      8, 8, 8, 2, 3, 4, 2, 5, 8,
      9, 9, 9, 3, 4, 1, 3, 6, 9
  };

  EXPECT_EQ(solver.IsValidInBoxes(input, 9, 0, 0), true);
  EXPECT_EQ(solver.IsValidInBoxes(input, 9, 3, 3), true);
  EXPECT_EQ(solver.IsValidInBoxes(input, 9, 6, 6), true);
}

TEST(SudokuSolverTest, IsValidInBoxesInvalid) {
  mila::sudokusolver::sequential::SudokuSolver solver;
  std::vector<int> input = {
      1, 2, 3, 1, 1, 1, 1, 1, 1,
      4, 5, 6, 1, 1, 1, 2, 2, 2,
      7, 8, 9, 1, 1, 1, 3, 3, 3,
      4, 4, 4, 9, 8, 7, 4, 4, 4,
      5, 5, 5, 6, 5, 4, 5, 5, 5,
      6, 6, 6, 3, 2, 1, 6, 6, 6,
      7, 7, 7, 1, 2, 3, 1, 4, 7,
      8, 8, 8, 2, 3, 4, 2, 5, 8,
      9, 9, 9, 3, 4, 1, 3, 6, 9
  };

  EXPECT_EQ(solver.IsValidInBoxes(input, 9, 3, 0), false);
  EXPECT_EQ(solver.IsValidInBoxes(input, 9, 0, 6), false);
  EXPECT_EQ(solver.IsValidInBoxes(input, 9, 3, 6), false);
}

TEST(SudokuSolverTest, IsValidMoveValid) {
  mila::sudokusolver::sequential::SudokuSolver solver;
  std::vector<int> input = {
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

  EXPECT_EQ(solver.IsValidMove(input, 9, 0), true);
  EXPECT_EQ(solver.IsValidMove(input, 9, 9), true);
  EXPECT_EQ(solver.IsValidMove(input, 9, 18), true);
}

TEST(SudokuSolverTest, IsValidMoveInvalid) {
  mila::sudokusolver::sequential::SudokuSolver solver;
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

  EXPECT_EQ(solver.IsValidMove(input, 9, 0), false);
  EXPECT_EQ(solver.IsValidMove(input, 9, 3), false);
  EXPECT_EQ(solver.IsValidMove(input, 9, 6), false);
}
