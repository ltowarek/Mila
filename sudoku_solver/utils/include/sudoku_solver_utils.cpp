#include "sudoku_solver_utils.h"

mila::sudokusolver::utils::SudokuFile::SudokuFile(): SudokuFile("") {}

mila::sudokusolver::utils::SudokuFile::SudokuFile(const std::string& file_name): file_name_(file_name) {}

std::vector<int> mila::sudokusolver::utils::SudokuFile::Read() const {
  std::ifstream file(file_name_);
  auto grid = std::vector<int>(std::istream_iterator<int>(file), std::istream_iterator<int>());
  file.close();
  return grid;
}

void mila::sudokusolver::utils::SudokuFile::Write(const std::vector<int> &grid) const {
  std::ofstream file(file_name_);
  std::ostream_iterator<int> iterator(file, " ");
  std::copy(grid.begin(), grid.end(), iterator);
  file.close();
}

std::string mila::sudokusolver::utils::SudokuFile::file_name() const {
  return file_name_;
}
