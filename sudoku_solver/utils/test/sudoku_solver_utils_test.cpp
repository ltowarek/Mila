#include "gtest/gtest.h"
#include "sudoku_solver_utils.h"

TEST(SudokuSolverUtilsSudokuFileTest, DefaultConstructor) {
  mila::sudokusolver::utils::SudokuFile file;
  EXPECT_EQ(file.file_name(), "");
}

TEST(SudokuSolverUtilsSudokuFileTest, Constructor) {
  mila::sudokusolver::utils::SudokuFile file("file name");
  EXPECT_EQ(file.file_name(), "file name");
}

TEST(SudokuSolverUtilsSudokuFileTest, Read) {
  mila::sudokusolver::utils::SudokuFile file("test_file.txt");
  std::vector<int> expected_output {
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

  std::vector<int> output = file.Read();

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverUtilsSudokuFileTest, Write) {
  mila::sudokusolver::utils::SudokuFile file("test_file_output.txt");
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

  file.Write(input);

  std::vector<int> output = file.Read();

  ASSERT_EQ(input.size(), output.size());
  for (int i = 0; i < input.size(); ++i) {
    EXPECT_EQ(input[i], output[i]);
  }
}
