#include "gtest/gtest.h"
#include "sudoku_solver_utils.h"

TEST(SudokuUtilsTest, FindEmptyCellsEmpty) {
  std::vector<int> input = {};
  std::vector<int> expected_output = {};

  std::vector<int> output = mila::sudokusolver::utils::FindEmptyCells(input);

  EXPECT_EQ(expected_output.size(), output.size());
}

TEST(SudokuUtilsTest, FindEmptyCellsNoEmptyCells) {
  std::vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> expected_output = {};

  std::vector<int> output = mila::sudokusolver::utils::FindEmptyCells(input);

  EXPECT_EQ(expected_output.size(), output.size());
}

TEST(SudokuUtilsTest, FindEmptyCells) {
  std::vector<int> input = {1, 2, 0, 4, 0, 0, 7, 8, 0};
  std::vector<int> expected_output = {2, 4, 5, 8};

  std::vector<int> output = mila::sudokusolver::utils::FindEmptyCells(input);

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

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
