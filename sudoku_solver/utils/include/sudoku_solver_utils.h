#ifndef MILA_SUDOKU_SOLVER_UTILS_H_
#define MILA_SUDOKU_SOLVER_UTILS_H_

#include <fstream>
#include <iterator>
#include <vector>
#include <string>

namespace mila {
namespace sudokusolver {
namespace utils {

class SudokuFile {
 public:
  SudokuFile();
  SudokuFile(const std::string& file_name);

  std::vector<int> Read() const;
  void Write(const std::vector<int>& grid) const;

  std::string file_name() const;
 private:
  const std::string file_name_;
};

}  // utils
}  // sudokusolver
}  // mila

#endif  // MILA_SUDOKU_SOLVER_UTILS_H_
