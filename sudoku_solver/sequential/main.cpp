#include <algorithm>
#include <stack>

void PrintGrid(const std::vector<int> &kGrid, const int kN) {
    for (int i = 0; i < kGrid.size(); ++i) {
        if ((i % kN) == 0) {
            printf("\n");
        }
        printf("%d", kGrid[i]);
    }
    printf("\n");
}

bool IsValidHorizontally(const std::vector<int> &kGrid, const int kN, const int kRow) {
    bool is_valid = true;
    std::vector<int> checked_numbers;

    for (int column = 0; column < kN; ++column) {
        int value = kGrid[kRow * kN + column];
        if (value != 0 && std::find(checked_numbers.begin(), checked_numbers.end(), value) != checked_numbers.end()) {
            is_valid = false;
            break;
        } else {
            checked_numbers.push_back(value);
        }
    }

    return is_valid;
}

bool IsValidVertically(const std::vector<int> &kGrid, const int kN, const int kColumn) {
    bool is_valid = true;
    std::vector<int> checked_numbers;

    for (int row = 0; row < kN; ++row) {
        int value = kGrid[row * kN + kColumn];
        if (value != 0 && std::find(checked_numbers.begin(), checked_numbers.end(), value) != checked_numbers.end()) {
            is_valid = false;
            break;
        } else {
            checked_numbers.push_back(value);
        }
    }

    return is_valid;
}

bool IsValidInBoxes(const std::vector<int> &kGrid, const int kN, const int kRow, const int kColumn) {
    const int kBoxSize = static_cast<int>(sqrt(kN));
    const int kBoxRow = kRow / kBoxSize;
    const int kBoxColumn = kColumn / kBoxSize;
    bool is_valid = true;
    std::vector<int> checked_numbers;

    for (int row = kBoxRow * kBoxSize; row < kBoxRow * kBoxSize + kBoxSize; ++row) {
        for (int column = kBoxColumn * kBoxSize; column < kBoxColumn * kBoxSize + kBoxSize; ++column) {
            int value = kGrid[row * kN + column];
            if (value != 0 && std::find(checked_numbers.begin(), checked_numbers.end(), value) != checked_numbers.end()) {
                is_valid = false;
                break;
            } else {
                checked_numbers.push_back(value);
            }
        }
    }

    return is_valid;
}

bool IsValid(const std::vector<int> &kGrid, const int kN, const int kId) {
    const int kRow = kId / kN;
    const int kColumn = kId % kN;
    return kGrid[kId] >= 1 &&
           kGrid[kId] <= kN &&
           IsValidHorizontally(kGrid, kN, kRow) &&
           IsValidVertically(kGrid, kN, kColumn) &&
           IsValidInBoxes(kGrid, kN, kRow, kColumn);
}

void FindEmptyCells(const std::vector<int> &kInputGrid, std::vector<int> &output_grid) {
    for (int i = 0; i < kInputGrid.size(); ++i) {
        if (kInputGrid[i] == 0) {
            output_grid.push_back(i);
        }
    }
}

bool Solve(const int kN, const std::vector<int> &kEmptyCells, std::vector<int> &grid) {
    bool is_solved = false;
    int current_empty_cell = 0;
    int number_of_empty_cells = kEmptyCells.size();

    while ((current_empty_cell >= 0) && (current_empty_cell < number_of_empty_cells)) {
        int id = kEmptyCells[current_empty_cell];
        grid[id]++;
        if (IsValid(grid, kN, id)) {
            current_empty_cell++;
        } else if (grid[id] >= kN) {
            grid[id] = 0;
            current_empty_cell--;
        }
    }

    if (current_empty_cell == number_of_empty_cells) {
        is_solved = true;
    }
    return is_solved;
}

int main() {
    const int kN = 9;
    const std::vector<int> kSolution {
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
    std::vector<int> grid {
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

    std::vector<int> empty_cells;
    FindEmptyCells(grid, empty_cells);

    bool is_solved = Solve(kN, empty_cells, grid);

    PrintGrid(grid, kN);

    if (is_solved) {
        printf("Sudoku solved successfully\n");

        if (grid != kSolution) {
            printf("Wrong solution!");
        } else {
            printf("Correct solution!\n");
        }
    } else {
        printf("Failed to solve sudoku!\n");
    }

    return 0;
}