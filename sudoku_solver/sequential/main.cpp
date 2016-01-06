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

bool IsValidHorizontally(const std::vector<int> &kGrid, const int kN, const int kRow, const int kColumn, const int kValue) {
    bool is_valid = true;
    for (int column = 0; column < kN; ++column) {
        if (column == kColumn) {
            continue;
        }
        if (kGrid[kRow * kN + column] == kValue) {
            is_valid = false;
            break;
        }
    }
    return is_valid;
}

bool IsValidVertically(const std::vector<int> &kGrid, const int kN, const int kRow, const int kColumn, const int kValue) {
    bool is_valid = true;
    for (int row = 0; row < kN; ++row) {
        if (row == kRow) {
            continue;
        }
        if (kGrid[row * kN + kColumn] == kValue) {
            is_valid = false;
            break;
        }
    }
    return is_valid;
}

bool IsValidInBoxes(const std::vector<int> &kGrid, const int kN, const int kRow, const int kColumn, const int kValue) {
    const int kBoxSize = static_cast<int>(sqrt(kN));
    const int kBoxRow = kRow / kBoxSize;
    const int kBoxColumn = kColumn / kBoxSize;
    bool is_valid = true;
    for (int row = kBoxRow * kBoxSize; row < kBoxRow * kBoxSize + kBoxSize; ++row) {
        for (int column = kBoxColumn * kBoxSize; column < kBoxColumn * kBoxSize + kBoxSize; ++column) {
            if ((row == kRow) && (column == kColumn)) {
                continue;
            }
            if (kGrid[row * kN + column] == kValue) {
                is_valid = false;
                break;
            }
        }
    }
    return is_valid;
}

bool IsValid(const std::vector<int> &kGrid, const int kN, const int kId, const int kValue) {
    const int kRow = kId / kN;
    const int kColumn = kId % kN;
    return IsValidHorizontally(kGrid, kN, kRow, kColumn, kValue) &&
           IsValidVertically(kGrid, kN, kRow, kColumn, kValue) &&
           IsValidInBoxes(kGrid, kN, kRow, kColumn, kValue);
}

void FindEmptyCells(const std::vector<int> &kInputGrid, std::vector<int> &output_grid) {
    for (int i = 0; i < kInputGrid.size(); ++i) {
        if (kInputGrid[i] == 0) {
            output_grid.push_back(i);
        }
    }
}

int GetNextEmptyCell(const std::vector<int> &kEmptyCells, const int current_empty_cell) {
    int next_empty_cell = -1;
    if (current_empty_cell + 1 < kEmptyCells.size()) {
        next_empty_cell = kEmptyCells[current_empty_cell + 1];
    }
    return next_empty_cell;
}

bool Solve(const int kN, const std::vector<int> &kEmptyCells, std::vector<int> &grid) {
    int current_empty_cell = -1;

    int id = GetNextEmptyCell(kEmptyCells, current_empty_cell);
    for (int value = 1; value <= kN; ++value) {
        if (IsValid(grid, kN, id, value)) {
            grid[id] = value;
            current_empty_cell++;
            break;
        }
    }

    while ((id = GetNextEmptyCell(kEmptyCells, current_empty_cell)) != -1) {
        // Try to fill an empty cell
        for (int value = 1; value <= kN; ++value) {
            if (IsValid(grid, kN, id, value)) {
                grid[id] = value;
                current_empty_cell++;
                break;
            }
        }

        // The cell was not filled
        if (grid[id] == 0) {
            int last_id = id;
            while (grid[last_id] == 0) {
                if (current_empty_cell >= 0) {
                    // Backtrack to the latest filled cell
                    last_id = kEmptyCells[current_empty_cell];
                    current_empty_cell--;

                    // Try to find new value for the latest filled cell
                    int last_value = grid[last_id];
                    grid[last_id] = 0;
                    for (int value = last_value + 1; value <= kN; ++value) {
                        if (IsValid(grid, kN, last_id, value)) {
                            grid[last_id] = value;
                            current_empty_cell++;
                            break;
                        }
                    }
                } else {
                    return false;
                }
            }
        }
    }
    return true;
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

    Solve(kN, empty_cells, grid);

    PrintGrid(grid, kN);

    if (grid != kSolution) {
        printf("Wrong solution!");
    } else {
        printf("Correct solution!");
    }

    return 0;
}