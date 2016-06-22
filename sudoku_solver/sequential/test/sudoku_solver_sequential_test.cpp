#include "gtest/gtest.h"
#include "sudoku_solver_sequential.h"
#include "sudoku_solver_sequential_profiler.h"

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

TEST(SudokuSolverTest, RunSuccess) {
  mila::sudokusolver::sequential::SudokuSolver solver;
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

TEST(SudokuSolverTest, RunFailure) {
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

  std::vector<int> output = solver.Run(input, 9);

  EXPECT_TRUE(std::find(output.begin(), output.end(), 0) != output.end());
}

TEST(SudokuSolverProfilerTest, RunWithoutProfiler) {
  mila::sudokusolver::sequential::SudokuSolverProfiler solver;
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

TEST(SudokuSolverProfilerTest, RunWithProfiler) {
  mila::sudokusolver::sequential::SudokuSolverProfiler solver;
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

  EXPECT_EQ(solver.results().count("Run"), 0);
  solver.Run(input, 9);
  EXPECT_EQ(solver.results().count("Run"), 1);
}

TEST(SudokuSolverBasedOnFilesTest, RunWithoutFiles) {
  mila::sudokusolver::sequential::SudokuSolverBasedOnFiles solver;
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

TEST(SudokuSolverBasedOnFilesTest, RunWithFiles) {
  mila::sudokusolver::sequential::SudokuSolverBasedOnFiles solver;
  std::string input_file_name = "test_file.txt";
  std::string output_file_name = "test_file_output.txt";
  std::string reference_file_name = "test_file_reference.txt";

  solver.Run(input_file_name, output_file_name);

  mila::sudokusolver::utils::SudokuFile output_file = mila::sudokusolver::utils::SudokuFile(output_file_name);
  mila::sudokusolver::utils::SudokuFile reference_file = mila::sudokusolver::utils::SudokuFile(reference_file_name);

  std::vector<int> output = output_file.Read();
  std::vector<int> expected_output = reference_file.Read();

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverBasedOnFilesProfilerTest, RunWithoutFilesWithoutProfiler) {
  mila::sudokusolver::sequential::SudokuSolverBasedOnFilesProfiler solver;
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

TEST(SudokuSolverBasedOnFilesProfilerTest, RunWithFilesWithoutProfiler) {
  mila::sudokusolver::sequential::SudokuSolverBasedOnFilesProfiler solver;
  std::string input_file_name = "test_file.txt";
  std::string output_file_name = "test_file_output.txt";
  std::string reference_file_name = "test_file_reference.txt";

  solver.Run(input_file_name, output_file_name);

  mila::sudokusolver::utils::SudokuFile output_file = mila::sudokusolver::utils::SudokuFile(output_file_name);
  mila::sudokusolver::utils::SudokuFile reference_file = mila::sudokusolver::utils::SudokuFile(reference_file_name);

  std::vector<int> output = output_file.Read();
  std::vector<int> expected_output = reference_file.Read();

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverBasedOnFilesProfilerTest, RunWithoutFilesWithProfiler) {
  mila::sudokusolver::sequential::SudokuSolverBasedOnFilesProfiler solver;
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

  EXPECT_EQ(solver.results().count("RunWithoutFiles"), 0);
  solver.Run(input, 9);
  EXPECT_EQ(solver.results().count("RunWithoutFiles"), 1);
}

TEST(SudokuSolverBasedOnFilesProfilerTest, RunWithFilesWithProfiler) {
  mila::sudokusolver::sequential::SudokuSolverBasedOnFilesProfiler solver;
  std::string input_file_name = "test_file.txt";
  std::string output_file_name = "test_file_output.txt";

  EXPECT_EQ(solver.results().count("RunWithFiles"), 0);
  solver.Run(input_file_name, output_file_name);
  EXPECT_EQ(solver.results().count("RunWithFiles"), 1);
}