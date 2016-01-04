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

int GetEmptyCell(const std::vector<int> &kGrid) {
    int empty_cell = -1;
    for (int i = 0; i < kGrid.size(); ++i) {
        if (kGrid[i] == 0) {
            empty_cell = i;
            break;
        }
    }
    return empty_cell;
}

bool Solve(const int kN, std::vector<int> &grid) {
    std::stack<int> steps;

    int id = GetEmptyCell(grid);
    for (int value = 1; value <= kN; ++value) {
        if (IsValid(grid, kN, id, value)) {
            grid[id] = value;
            steps.push(id);
            break;
        }
    }

    while ((id = GetEmptyCell(grid)) != -1) {
        // Try to fill an empty cell
        for (int value = 1; value <= kN; ++value) {
            if (IsValid(grid, kN, id, value)) {
                grid[id] = value;
                steps.push(id);
                break;
            }
        }

        // The cell was not filled
        if (grid[id] == 0) {
            int last_id = id;
            while (grid[last_id] == 0) {
                if (!steps.empty()) {
                    // Backtrack to the latest filled cell
                    last_id = steps.top();
                    steps.pop();

                    // Try to find new value for the latest filled cell
                    int last_value = grid[last_id];
                    grid[last_id] = 0;
                    for (int value = last_value + 1; value <= kN; ++value) {
                        if (IsValid(grid, kN, last_id, value)) {
                            grid[last_id] = value;
                            steps.push(last_id);
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
    const int kN = 16;
    const std::vector<int> kSolution {
            7, 14, 6, 9, 8, 5, 1, 12, 3, 11, 2, 16, 4, 10, 13, 15,
            12, 8, 13, 5, 7, 15, 14, 3, 4, 6, 9, 10, 11, 1, 16, 2,
            4, 15, 10, 2, 13, 16, 11, 6, 1, 7, 12, 5, 8, 9, 3, 14,
            1, 3, 11, 16, 2, 9, 4, 10, 8, 14, 13, 15, 7, 5, 6, 12,
            6, 10, 1, 13, 14, 2, 3, 9, 15, 4, 16, 12, 5, 7, 8, 11,
            15, 5, 9, 3, 10, 13, 16, 11, 2, 8, 7, 14, 6, 12, 1, 4,
            14, 4, 16, 8, 1, 12, 7, 15, 11, 5, 6, 3, 10, 2, 9, 13,
            2, 11, 12, 7, 5, 4, 6, 8, 9, 1, 10, 13, 16, 15, 14, 3,
            13, 7, 5, 1, 12, 6, 2, 14, 16, 15, 3, 11, 9, 8, 4, 10,
            8, 6, 4, 15, 16, 10, 13, 5, 7, 12, 14, 9, 2, 3, 11, 1,
            11, 16, 14, 12, 4, 3, 9, 7, 10, 2, 1, 8, 15, 13, 5, 6,
            3, 9, 2, 10, 15, 11, 8, 1, 6, 13, 5, 4, 12, 14, 7, 16,
            16, 12, 3, 6, 11, 14, 15, 13, 5, 10, 8, 7, 1, 4, 2, 9,
            9, 2, 7, 14, 6, 8, 12, 4, 13, 16, 15, 1, 3, 11, 10, 5,
            5, 13, 8, 4, 3, 1, 10, 2, 12, 9, 11, 6, 14, 16, 15, 7,
            10, 1, 15, 11, 9, 7, 5, 16, 14, 3, 4, 2, 13, 6, 12, 8
    };
    std::vector<int> grid {
            7, 0, 0, 0, 0, 5, 1, 0, 3, 11, 0, 0, 0, 0, 0, 0,
            12, 8, 0, 0, 0, 15, 14, 0, 4, 0, 9, 0, 11, 0, 16, 2,
            0, 15, 10, 2, 13, 0, 0, 0, 0, 7, 0, 5, 8, 0, 3, 0,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 1, 0, 0, 2, 0, 0, 15, 0, 0, 0, 5, 0, 0, 11,
            15, 0, 0, 3, 0, 0, 0, 0, 0, 0, 7, 14, 6, 0, 1, 0,
            14, 0, 16, 0, 0, 0, 0, 0, 0, 5, 6, 0, 10, 2, 0, 0,
            0, 0, 12, 0, 0, 0, 0, 8, 9, 1, 10, 13, 16, 0, 0, 3,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 9, 8, 0, 0,
            0, 6, 4, 0, 0, 10, 0, 0, 7, 0, 14, 0, 0, 0, 11, 0,
            0, 16, 0, 12, 0, 3, 9, 0, 10, 0, 0, 8, 0, 0, 5, 0,
            3, 0, 0, 0, 15, 0, 0, 0, 0, 13, 0, 4, 0, 14, 0, 16,
            0, 0, 0, 0, 0, 14, 15, 13, 0, 10, 8, 0, 0, 4, 0, 9,
            9, 0, 7, 0, 6, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
            5, 13, 8, 0, 3, 0, 10, 0, 0, 0, 11, 6, 0, 0, 15, 0,
            10, 1, 15, 0, 0, 0, 5, 16, 14, 0, 4, 0, 0, 6, 0, 0
    };

    Solve(kN, grid);

    if (grid != kSolution) {
        printf("Wrong solution!");
    } else {
        printf("Correct solution!");
    }

    return 0;
}