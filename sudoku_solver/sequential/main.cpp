#include "utils.h"
#include "version.h"
#include "sudoku_solver_sequential_profiler.h"

struct parameters {
  std::string input_file;
  std::string output_file;
  size_t number_of_iterations;
};

parameters ParseCommandLine(int argc, char **argv) {
  auto config = parameters{};
  // TODO: Verify input and add help message
  config.input_file = std::string(argv[1]);
  config.output_file = std::string(argv[2]);
  config.number_of_iterations = static_cast<size_t>(atoi(argv[3]));
  return config;
}

int main(int argc, char **argv) {
  auto config = ParseCommandLine(argc, argv);
  printf("%s\n", mila::version::GetVersion().c_str());

  auto sudoku_solver_initial = mila::sudokusolver::sequential::SudokuSolverBasedOnFilesProfiler();
  sudoku_solver_initial.Run(config.input_file, config.output_file);
  auto duration = sudoku_solver_initial.results().at(sudoku_solver_initial.main_result());
  printf("Initial results\n");
  printf("Duration [us]: %lld\n", duration);
  printf("Input file: %s\n", config.input_file.c_str());
  printf("Output file: %s\n", config.output_file.c_str());

  auto results = std::vector<float>(config.number_of_iterations);
  printf("Iterations\n");
  for (size_t i = 0; i < config.number_of_iterations; ++i) {
    auto sudoku_solver = mila::sudokusolver::sequential::SudokuSolverBasedOnFilesProfiler();
    sudoku_solver.Run(config.input_file, config.output_file);
    duration = sudoku_solver.results().at(sudoku_solver.main_result());
    printf("Iteration: %d, Duration [us]: %lld\n", i, duration);
    results[i] = duration;
  }

  printf("Statistics\n");
  printf("Mean: %f\n", mila::utils::Mean(results));
  printf("Median: %f\n", mila::utils::Median(results));
  printf("Variance: %f\n", mila::utils::Variance(results));
  printf("Standard Deviation: %f\n", mila::utils::StandardDeviation(results));
  printf("Coefficient of Variation: %f\n", mila::utils::CoefficientOfVariation(results));

  return 0;
}
