#include "gtest/gtest.h"
#include "sudoku_solver_parallel.h"
#include "sudoku_solver_parallel_profiler.h"

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

TEST(SudokuSolverParallelTest, Run8FilledCells) {
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

  std::vector<int> output = solver.Run(input, 8);

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverParallelTest, Run10FilledCells) {
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

  std::vector<int> output = solver.Run(input, 10);

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverParallelTest, Run15FilledCells) {
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

  std::vector<int> output = solver.Run(input, 15);

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverParallelTest, GeneratePossibleSolutions1CellSimpleGrids) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  int number_of_cells_to_fill = 1;
  std::vector<int> input = {
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  std::vector<int> expected_grids = {
      9, 1, 2, 3, 4, 5, 6, 7, 8,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  std::vector<int> grids;
  int number_of_grids;
  std::vector<int> empty_cells;
  std::vector<int> numbers_of_empty_cells_per_grid;

  std::tie(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid) = solver.GeneratePossibleSolutions(input, number_of_cells_to_fill);

  ASSERT_LE(expected_grids.size(), grids.size());
  for (int i = 0; i < expected_grids.size(); ++i) {
    EXPECT_EQ(expected_grids[i], grids[i]);
  }
}

TEST(SudokuSolverParallelTest, GeneratePossibleSolutions1CellSimpleNumberOfGrids) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  int number_of_cells_to_fill = 1;
  std::vector<int> input = {
      0, 1, 2, 3, 4, 5, 6, 7, 8,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  int expected_number_of_grids = 1;

  std::vector<int> grids;
  int number_of_grids;
  std::vector<int> empty_cells;
  std::vector<int> numbers_of_empty_cells_per_grid;

  std::tie(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid) = solver.GeneratePossibleSolutions(input, number_of_cells_to_fill);

  EXPECT_EQ(expected_number_of_grids, number_of_grids);
}

TEST(SudokuSolverParallelTest, GeneratePossibleSolutions1CellSimpleEmptyCells) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  int number_of_cells_to_fill = 1;
  std::vector<int> input = {
      0, 1, 2, 3, 4, 5, 6, 7, 8,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  std::vector<int> expected_empty_cells = {
      9, 10, 11, 12, 13, 14, 15, 16, 17,
      18, 19, 20, 21, 22, 23, 24, 25, 26,
      27, 28, 29, 30, 31, 32, 33, 34, 35,
      36, 37, 38, 39, 40, 41, 42, 43, 44,
      45, 46, 47, 48, 49, 50, 51, 52, 53,
      54, 55, 56, 57, 58, 59, 60, 61, 62,
      63, 64, 65, 66, 67, 68, 69, 70, 71,
      72, 73, 74, 75, 76, 77, 78, 79, 80,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  std::vector<int> grids;
  int number_of_grids;
  std::vector<int> empty_cells;
  std::vector<int> numbers_of_empty_cells_per_grid;

  std::tie(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid) = solver.GeneratePossibleSolutions(input, number_of_cells_to_fill);

  ASSERT_LE(expected_empty_cells.size(), empty_cells.size());
  for (int i = 0; i < expected_empty_cells.size(); ++i) {
    EXPECT_EQ(expected_empty_cells[i], empty_cells[i]);
  }
}

TEST(SudokuSolverParallelTest, GeneratePossibleSolutions1CellSimpleNumbersOfEmptyCells) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  int number_of_cells_to_fill = 1;
  std::vector<int> input = {
      0, 1, 2, 3, 4, 5, 6, 7, 8,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  std::vector<int> expected_numbers_of_empty_cells_per_grid = {
      72
  };

  std::vector<int> grids;
  int number_of_grids;
  std::vector<int> empty_cells;
  std::vector<int> numbers_of_empty_cells_per_grid;

  std::tie(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid) = solver.GeneratePossibleSolutions(input, number_of_cells_to_fill);

  ASSERT_LE(expected_numbers_of_empty_cells_per_grid.size(), numbers_of_empty_cells_per_grid.size());
  for (int i = 0; i < expected_numbers_of_empty_cells_per_grid.size(); ++i) {
    EXPECT_EQ(expected_numbers_of_empty_cells_per_grid[i], numbers_of_empty_cells_per_grid[i]);
  }
}

TEST(SudokuSolverParallelTest, GeneratePossibleSolutions1CellComplexGrids) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  int number_of_cells_to_fill = 1;
  std::vector<int> input = {
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8
  };
  std::vector<int> expected_grids = {
      1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8,
      2, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8,
      3, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8,
      4, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8,
      5, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8,
      6, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8,
      7, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8,
      8, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8,
      9, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8
  };

  std::vector<int> grids;
  int number_of_grids;
  std::vector<int> empty_cells;
  std::vector<int> numbers_of_empty_cells_per_grid;

  std::tie(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid) = solver.GeneratePossibleSolutions(input, number_of_cells_to_fill);

  ASSERT_LE(expected_grids.size(), grids.size());
  for (int i = 0; i < expected_grids.size(); ++i) {
    EXPECT_EQ(expected_grids[i], grids[i]);
  }
}

TEST(SudokuSolverParallelTest, GeneratePossibleSolutions1CellComplexNumberOfGrids) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  int number_of_cells_to_fill = 1;
  std::vector<int> input = {
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8
  };
  int expected_number_of_grids = 9;

  std::vector<int> grids;
  int number_of_grids;
  std::vector<int> empty_cells;
  std::vector<int> numbers_of_empty_cells_per_grid;

  std::tie(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid) = solver.GeneratePossibleSolutions(input, number_of_cells_to_fill);

  EXPECT_EQ(expected_number_of_grids, number_of_grids);
}

TEST(SudokuSolverParallelTest, GeneratePossibleSolutions1CellComplexEmptyCells) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  int number_of_cells_to_fill = 1;
  std::vector<int> input = {
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8
  };
  std::vector<int> expected_empty_cells = {
      1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18,
      19, 20, 21, 22, 23, 24, 25, 26, 27,
      28, 29, 30, 31, 32, 33, 34, 35, 36,
      37, 38, 39, 40, 41, 42, 43, 44, 45,
      46, 47, 48, 49, 50, 51, 52, 53, 54,
      55, 56, 57, 58, 59, 60, 61, 62, 63,
      64, 65, 66, 67, 68, 69, 70, 71, 72,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18,
      19, 20, 21, 22, 23, 24, 25, 26, 27,
      28, 29, 30, 31, 32, 33, 34, 35, 36,
      37, 38, 39, 40, 41, 42, 43, 44, 45,
      46, 47, 48, 49, 50, 51, 52, 53, 54,
      55, 56, 57, 58, 59, 60, 61, 62, 63,
      64, 65, 66, 67, 68, 69, 70, 71, 72,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18,
      19, 20, 21, 22, 23, 24, 25, 26, 27,
      28, 29, 30, 31, 32, 33, 34, 35, 36,
      37, 38, 39, 40, 41, 42, 43, 44, 45,
      46, 47, 48, 49, 50, 51, 52, 53, 54,
      55, 56, 57, 58, 59, 60, 61, 62, 63,
      64, 65, 66, 67, 68, 69, 70, 71, 72,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18,
      19, 20, 21, 22, 23, 24, 25, 26, 27,
      28, 29, 30, 31, 32, 33, 34, 35, 36,
      37, 38, 39, 40, 41, 42, 43, 44, 45,
      46, 47, 48, 49, 50, 51, 52, 53, 54,
      55, 56, 57, 58, 59, 60, 61, 62, 63,
      64, 65, 66, 67, 68, 69, 70, 71, 72,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18,
      19, 20, 21, 22, 23, 24, 25, 26, 27,
      28, 29, 30, 31, 32, 33, 34, 35, 36,
      37, 38, 39, 40, 41, 42, 43, 44, 45,
      46, 47, 48, 49, 50, 51, 52, 53, 54,
      55, 56, 57, 58, 59, 60, 61, 62, 63,
      64, 65, 66, 67, 68, 69, 70, 71, 72,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18,
      19, 20, 21, 22, 23, 24, 25, 26, 27,
      28, 29, 30, 31, 32, 33, 34, 35, 36,
      37, 38, 39, 40, 41, 42, 43, 44, 45,
      46, 47, 48, 49, 50, 51, 52, 53, 54,
      55, 56, 57, 58, 59, 60, 61, 62, 63,
      64, 65, 66, 67, 68, 69, 70, 71, 72,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18,
      19, 20, 21, 22, 23, 24, 25, 26, 27,
      28, 29, 30, 31, 32, 33, 34, 35, 36,
      37, 38, 39, 40, 41, 42, 43, 44, 45,
      46, 47, 48, 49, 50, 51, 52, 53, 54,
      55, 56, 57, 58, 59, 60, 61, 62, 63,
      64, 65, 66, 67, 68, 69, 70, 71, 72,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18,
      19, 20, 21, 22, 23, 24, 25, 26, 27,
      28, 29, 30, 31, 32, 33, 34, 35, 36,
      37, 38, 39, 40, 41, 42, 43, 44, 45,
      46, 47, 48, 49, 50, 51, 52, 53, 54,
      55, 56, 57, 58, 59, 60, 61, 62, 63,
      64, 65, 66, 67, 68, 69, 70, 71, 72,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18,
      19, 20, 21, 22, 23, 24, 25, 26, 27,
      28, 29, 30, 31, 32, 33, 34, 35, 36,
      37, 38, 39, 40, 41, 42, 43, 44, 45,
      46, 47, 48, 49, 50, 51, 52, 53, 54,
      55, 56, 57, 58, 59, 60, 61, 62, 63,
      64, 65, 66, 67, 68, 69, 70, 71, 72,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  std::vector<int> grids;
  int number_of_grids;
  std::vector<int> empty_cells;
  std::vector<int> numbers_of_empty_cells_per_grid;

  std::tie(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid) = solver.GeneratePossibleSolutions(input, number_of_cells_to_fill);

  ASSERT_LE(expected_empty_cells.size(), empty_cells.size());
  for (int i = 0; i < expected_empty_cells.size(); ++i) {
    EXPECT_EQ(expected_empty_cells[i], empty_cells[i]);
  }
}

TEST(SudokuSolverParallelTest, GeneratePossibleSolutions1CellComplexNumbersOfEmptyCells) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  int number_of_cells_to_fill = 1;
  std::vector<int> input = {
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8
  };
  std::vector<int> expected_numbers_of_empty_cells_per_grid = {
      72, 72, 72, 72, 72, 72, 72, 72, 72
  };

  std::vector<int> grids;
  int number_of_grids;
  std::vector<int> empty_cells;
  std::vector<int> numbers_of_empty_cells_per_grid;

  std::tie(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid) = solver.GeneratePossibleSolutions(input, number_of_cells_to_fill);

  ASSERT_LE(expected_numbers_of_empty_cells_per_grid.size(), numbers_of_empty_cells_per_grid.size());
  for (int i = 0; i < expected_numbers_of_empty_cells_per_grid.size(); ++i) {
    EXPECT_EQ(expected_numbers_of_empty_cells_per_grid[i], numbers_of_empty_cells_per_grid[i]);
  }
}

TEST(SudokuSolverParallelTest, GeneratePossibleSolutions2CellsSimpleGrids) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  int number_of_cells_to_fill = 2;
  std::vector<int> input = {
      0, 0, 2, 3, 4, 5, 6, 7, 8,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  std::vector<int> expected_grids_1 = {
      1, 9, 2, 3, 4, 5, 6, 7, 8,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      9, 1, 2, 3, 4, 5, 6, 7, 8,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  std::vector<int> expected_grids_2 = {
      9, 1, 2, 3, 4, 5, 6, 7, 8,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 9, 2, 3, 4, 5, 6, 7, 8,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
  };

  std::vector<int> grids;
  int number_of_grids;
  std::vector<int> empty_cells;
  std::vector<int> numbers_of_empty_cells_per_grid;

  std::tie(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid) = solver.GeneratePossibleSolutions(input, number_of_cells_to_fill);

  ASSERT_LE(expected_grids_1.size(), grids.size());
  ASSERT_LE(expected_grids_2.size(), grids.size());
  // Implementation defines which thread start firs so we cannot assume the order of grid,
  // but we can check wheter all expected values are in the output.
  if (grids[0] == 1) {
    for (int i = 0; i < expected_grids_1.size(); ++i) {
      EXPECT_EQ(expected_grids_1[i], grids[i]);
    }
  } else {
    for (int i = 0; i < expected_grids_2.size(); ++i) {
      EXPECT_EQ(expected_grids_2[i], grids[i]);
    }
  }
}

TEST(SudokuSolverParallelTest, GeneratePossibleSolutions2CellsSimpleNumberOfGrids) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  int number_of_cells_to_fill = 2;
  std::vector<int> input = {
      0, 0, 2, 3, 4, 5, 6, 7, 8,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  int expected_number_of_grids = 2;

  std::vector<int> grids;
  int number_of_grids;
  std::vector<int> empty_cells;
  std::vector<int> numbers_of_empty_cells_per_grid;

  std::tie(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid) = solver.GeneratePossibleSolutions(input, number_of_cells_to_fill);

  EXPECT_EQ(expected_number_of_grids, number_of_grids);
}

TEST(SudokuSolverParallelTest, GeneratePossibleSolutions2CellsSimpleEmptyCells) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  int number_of_cells_to_fill = 2;
  std::vector<int> input = {
      0, 0, 2, 3, 4, 5, 6, 7, 8,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  std::vector<int> expected_empty_cells = {
      9, 10, 11, 12, 13, 14, 15, 16, 17,
      18, 19, 20, 21, 22, 23, 24, 25, 26,
      27, 28, 29, 30, 31, 32, 33, 34, 35,
      36, 37, 38, 39, 40, 41, 42, 43, 44,
      45, 46, 47, 48, 49, 50, 51, 52, 53,
      54, 55, 56, 57, 58, 59, 60, 61, 62,
      63, 64, 65, 66, 67, 68, 69, 70, 71,
      72, 73, 74, 75, 76, 77, 78, 79, 80,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      9, 10, 11, 12, 13, 14, 15, 16, 17,
      18, 19, 20, 21, 22, 23, 24, 25, 26,
      27, 28, 29, 30, 31, 32, 33, 34, 35,
      36, 37, 38, 39, 40, 41, 42, 43, 44,
      45, 46, 47, 48, 49, 50, 51, 52, 53,
      54, 55, 56, 57, 58, 59, 60, 61, 62,
      63, 64, 65, 66, 67, 68, 69, 70, 71,
      72, 73, 74, 75, 76, 77, 78, 79, 80,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  std::vector<int> grids;
  int number_of_grids;
  std::vector<int> empty_cells;
  std::vector<int> numbers_of_empty_cells_per_grid;

  std::tie(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid) = solver.GeneratePossibleSolutions(input, number_of_cells_to_fill);

  ASSERT_LE(expected_empty_cells.size(), empty_cells.size());
  for (int i = 0; i < expected_empty_cells.size(); ++i) {
    EXPECT_EQ(expected_empty_cells[i], empty_cells[i]);
  }
}

TEST(SudokuSolverParallelTest, GeneratePossibleSolutions2CellsSimpleNumbersOfEmptyCells) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  int number_of_cells_to_fill = 2;
  std::vector<int> input = {
      0, 0, 2, 3, 4, 5, 6, 7, 8,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  std::vector<int> expected_numbers_of_empty_cells_per_grid = {
      72, 72
  };

  std::vector<int> grids;
  int number_of_grids;
  std::vector<int> empty_cells;
  std::vector<int> numbers_of_empty_cells_per_grid;

  std::tie(grids, number_of_grids, empty_cells, numbers_of_empty_cells_per_grid) = solver.GeneratePossibleSolutions(input, number_of_cells_to_fill);

  ASSERT_LE(expected_numbers_of_empty_cells_per_grid.size(), numbers_of_empty_cells_per_grid.size());
  for (int i = 0; i < expected_numbers_of_empty_cells_per_grid.size(); ++i) {
    EXPECT_EQ(expected_numbers_of_empty_cells_per_grid[i], numbers_of_empty_cells_per_grid[i]);
  }
}

TEST(SudokuSolverParallelTest, SolveSudoku1EmptyCell1Grid) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  std::vector<int> grids {
      9, 0, 4, 1, 3, 7, 6, 8, 2,
      2, 7, 3, 6, 8, 4, 1, 9, 5,
      1, 6, 8, 2, 9, 5, 7, 3, 4,
      4, 9, 5, 7, 2, 8, 3, 6, 1,
      6, 8, 1, 4, 5, 3, 2, 7, 9,
      3, 2, 7, 9, 6, 1, 5, 4, 8,
      7, 4, 9, 3, 1, 2, 8, 5, 6,
      5, 1, 6, 8, 7, 9, 4, 2, 3,
      8, 3, 2, 5, 4, 6, 9, 1, 7
  };
  int number_of_grids = 1;
  std::vector<int> empty_cells {
      1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  std::vector<int> numbers_of_empty_cells {
      1
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

  std::vector<int> output = solver.SolveSudoku(grids, number_of_grids, empty_cells, numbers_of_empty_cells);

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverParallelTest, SolveSudoku2EmptyCells1Grid) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  std::vector<int> grids {
      9, 0, 0, 1, 3, 7, 6, 8, 2,
      2, 7, 3, 6, 8, 4, 1, 9, 5,
      1, 6, 8, 2, 9, 5, 7, 3, 4,
      4, 9, 5, 7, 2, 8, 3, 6, 1,
      6, 8, 1, 4, 5, 3, 2, 7, 9,
      3, 2, 7, 9, 6, 1, 5, 4, 8,
      7, 4, 9, 3, 1, 2, 8, 5, 6,
      5, 1, 6, 8, 7, 9, 4, 2, 3,
      8, 3, 2, 5, 4, 6, 9, 1, 7
  };
  int number_of_grids = 1;
  std::vector<int> empty_cells {
      1, 2, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  std::vector<int> numbers_of_empty_cells {
      2
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

  std::vector<int> output = solver.SolveSudoku(grids, number_of_grids, empty_cells, numbers_of_empty_cells);

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverParallelTest, SolveSudoku1EmptyCell2Grids) {
  mila::sudokusolver::parallel::SudokuSolver solver;
  std::vector<int> grids {
      9, 0, 4, 1, 3, 7, 6, 8, 2,
      2, 7, 3, 6, 8, 4, 1, 9, 5,
      1, 6, 8, 2, 9, 5, 7, 3, 4,
      4, 9, 5, 7, 2, 8, 3, 6, 1,
      6, 8, 1, 4, 5, 3, 2, 7, 9,
      3, 2, 7, 9, 6, 1, 5, 4, 8,
      7, 4, 9, 3, 1, 2, 8, 5, 6,
      5, 1, 6, 8, 7, 9, 4, 2, 3,
      8, 3, 2, 5, 4, 6, 9, 1, 7,

      8, 0, 4, 1, 3, 7, 6, 8, 2,
      2, 7, 3, 6, 8, 4, 1, 9, 5,
      1, 6, 8, 2, 9, 5, 7, 3, 4,
      4, 9, 5, 7, 2, 8, 3, 6, 1,
      6, 8, 1, 4, 5, 3, 2, 7, 9,
      3, 2, 7, 9, 6, 1, 5, 4, 8,
      7, 4, 9, 3, 1, 2, 8, 5, 6,
      5, 1, 6, 8, 7, 9, 4, 2, 3,
      8, 3, 2, 5, 4, 6, 9, 1, 7
  };
  int number_of_grids = 2;
  std::vector<int> empty_cells {
      1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,

      1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  std::vector<int> numbers_of_empty_cells {
      1, 1
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

  std::vector<int> output = solver.SolveSudoku(grids, number_of_grids, empty_cells, numbers_of_empty_cells);

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverParallelProfilerTest, Run10FilledCellsWithoutProfiler) {
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

  std::vector<int> output = solver.Run(input, 10);

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverParallelProfilerTest, Run10FilledCellsWithProfiler) {
  mila::sudokusolver::parallel::SudokuSolverProfiler solver;
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
  solver.Run(input, 10);
  EXPECT_EQ(solver.results().count("Run"), 1);
}

TEST(SudokuSolverParallelBasedOnFilesTest, Run10FilledCellsWithoutFiles) {
  mila::sudokusolver::parallel::SudokuSolverBasedOnFiles solver;
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

  std::vector<int> output = solver.Run(input, 10);

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverParallelBasedOnFilesTest, Run10FilledCellsWithFiles) {
  mila::sudokusolver::parallel::SudokuSolverBasedOnFiles solver;
  std::string input_file_name = "test_file.txt";
  std::string output_file_name = "test_file_output.txt";
  std::string reference_file_name = "test_file_reference.txt";

  solver.Run(input_file_name, output_file_name, 10);

  mila::sudokusolver::utils::SudokuFile output_file = mila::sudokusolver::utils::SudokuFile(output_file_name);
  mila::sudokusolver::utils::SudokuFile reference_file = mila::sudokusolver::utils::SudokuFile(reference_file_name);

  std::vector<int> output = output_file.Read();
  std::vector<int> expected_output = reference_file.Read();

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverParallelBasedOnFilesProfilerTest, Run10FilledCellsWithoutFilesWithoutProfiler) {
  mila::sudokusolver::parallel::SudokuSolverBasedOnFilesProfiler solver;
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

  std::vector<int> output = solver.Run(input, 10);

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverParallelBasedOnFilesProfilerTest, Run10FilledCellsWithoutFilesWithProfiler) {
  mila::sudokusolver::parallel::SudokuSolverBasedOnFilesProfiler solver;
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
  solver.Run(input, 10);
  EXPECT_EQ(solver.results().count("RunWithoutFiles"), 1);
}

TEST(SudokuSolverParallelBasedOnFilesProfilerTest, Run10FilledCellsWithFilesWithoutProfiler) {
  mila::sudokusolver::parallel::SudokuSolverBasedOnFilesProfiler solver;
  std::string input_file_name = "test_file.txt";
  std::string output_file_name = "test_file_output.txt";
  std::string reference_file_name = "test_file_reference.txt";

  solver.Run(input_file_name, output_file_name, 10);

  mila::sudokusolver::utils::SudokuFile output_file = mila::sudokusolver::utils::SudokuFile(output_file_name);
  mila::sudokusolver::utils::SudokuFile reference_file = mila::sudokusolver::utils::SudokuFile(reference_file_name);

  std::vector<int> output = output_file.Read();
  std::vector<int> expected_output = reference_file.Read();

  ASSERT_EQ(expected_output.size(), output.size());
  for (int i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(expected_output[i], output[i]);
  }
}

TEST(SudokuSolverParallelBasedOnFilesProfilerTest, Run10FilledCellsWithFilesWithProfiler) {
  mila::sudokusolver::parallel::SudokuSolverBasedOnFilesProfiler solver;
  std::string input_file_name = "test_file.txt";
  std::string output_file_name = "test_file_output.txt";

  EXPECT_EQ(solver.results().count("RunWithFiles"), 0);
  solver.Run(input_file_name, output_file_name, 10);
  EXPECT_EQ(solver.results().count("RunWithFiles"), 1);
}
