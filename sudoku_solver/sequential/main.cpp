#include <algorithm>
#include <stack>

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

bool Solve(const int kN, const int kId, std::vector<int> &grid) {
    if (grid[kId] != 0) {
        if (IsValid(grid, kN, kId, grid[kId])) {
            if (kId == kN * kN - 1 ) {
                return true;
            }
            return Solve(kN, kId + 1, grid);
        } else {
            return false;
        }
    }

    for (int i = 1; i <= kN; ++i) {
        if (IsValid(grid, kN, kId, i)) {
            grid[kId] = i;
            if (kId == kN * kN - 1 ) {
                return true;
            }
            if (Solve(kN, kId + 1, grid)) {
                return true;
            }
        }
    }

    grid[kId] = 0;
    return false;
}

int main() {
    const int kN = 9;

    const std::vector<int> kSolution {
            5, 3, 4, 6, 7, 8, 9, 1, 2,
            6, 7, 2, 1, 9, 5, 3, 4, 8,
            1, 9, 8, 3, 4, 2, 5, 6, 7,
            8, 5, 9, 7, 6, 1, 4, 2, 3,
            4, 2, 6, 8, 5, 3, 7, 9, 1,
            7, 1, 3, 9, 2, 4, 8, 5, 6,
            9, 6, 1, 5, 3, 7, 2, 8, 4,
            2, 8, 7, 4, 1, 9, 6, 3, 5,
            3, 4, 5, 2, 8, 6, 1, 7, 9
    };
    std::vector<int> grid {
            5, 3, 0, 0, 7, 0, 0, 0, 0,
            6, 0, 0, 1, 9, 5, 0, 0, 0,
            0, 9, 8, 0, 0, 0, 0, 6, 0,
            8, 0, 0, 0, 6, 0, 0, 0, 3,
            4, 0, 0, 8, 0, 3, 0, 0, 1,
            7, 0, 0, 0, 2, 0, 0, 0, 6,
            0, 6, 0, 0, 0, 0, 2, 8, 0,
            0, 0, 0, 4, 1, 9, 0, 0, 5,
            0, 0, 0, 0, 8, 0, 0, 7, 9
    };

    Solve(kN, 0, grid);

    if (grid != kSolution) {
        printf("Wrong solution!");
    } else {
        printf("Correct solution!");
    }

    return 0;
}