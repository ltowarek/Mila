// kN passed as a build option

bool IsValidHorizontally(int *kGrid, int kSize, int kRow, int kColumn, int kValue) {
    bool is_valid = true;
    for (int column = 0; column < kSize; ++column) {
        if (column == kColumn) {
            continue;
        }
        if (kGrid[kRow * kSize + column] == kValue) {
            is_valid = false;
            break;
        }
    }
    return is_valid;
}

bool IsValidVertically(int *kGrid, int kSize, int kRow, int kColumn, int kValue) {
    bool is_valid = true;
    for (int row = 0; row < kSize; ++row) {
        if (row == kRow) {
            continue;
        }
        if (kGrid[row * kSize + kColumn] == kValue) {
            is_valid = false;
            break;
        }
    }
    return is_valid;
}

bool IsValidInBoxes(int *kGrid, int kSize, int kRow, int kColumn, int kValue) {
    int kBoxSize = (int)sqrt((float)kSize);
    int kBoxRow = kRow / kBoxSize;
    int kBoxColumn = kColumn / kBoxSize;
    bool is_valid = true;
    for (int row = kBoxRow * kBoxSize; row < kBoxRow * kBoxSize + kBoxSize; ++row) {
        for (int column = kBoxColumn * kBoxSize; column < kBoxColumn * kBoxSize + kBoxSize; ++column) {
            if ((row == kRow) && (column == kColumn)) {
                continue;
            }
            if (kGrid[row * kSize + column] == kValue) {
                is_valid = false;
                break;
            }
        }
    }
    return is_valid;
}

bool IsValid(int *kGrid, int kSize, int kId, int kValue) {
    int kRow = kId / kSize;
    int kColumn = kId % kSize;
    return IsValidHorizontally(kGrid, kSize, kRow, kColumn, kValue) &&
           IsValidVertically(kGrid, kSize, kRow, kColumn, kValue) &&
           IsValidInBoxes(kGrid, kSize, kRow, kColumn, kValue);
}

int GetNextEmptyCell(constant int *kEmptyCells, int kSize, int current_empty_cell) {
    int next_empty_cell = -1;
    if (current_empty_cell + 1 < kSize) {
        next_empty_cell = kEmptyCells[current_empty_cell + 1];
    }
    return next_empty_cell;
}

kernel void SudokuSolverBFS(constant int *kOldGrids, global int *number_of_old_grids, global int *new_grids, global int *number_of_new_grids, global int *empty_cells, global int *numbers_of_empty_cells) {
    int tid = get_global_id(0);
    int number_of_threads = get_global_size(0);
    int current_old_grid = tid;

    // Iterate over all old grids
    while (current_old_grid < *number_of_old_grids) {
        // Get next board
        int grid[kN * kN];
        for (int i = 0; i < kN * kN; ++i) {
            grid[i] = kOldGrids[current_old_grid * kN * kN + i];
        }

        for (int i = 0; i < kN * kN; ++i) {
            // Find first empty cell
            if (grid[i] == 0) {
                // Fill this cell with all valid values
                for (int value = 1; value <= kN; ++value) {
                    if (IsValid(grid, kN, i, value)) {
                        grid[i] = value;
                        int next_new_grid = atomic_inc(number_of_new_grids);
                        int number_of_empty_cells = 0;
                        for (int j = 0; j < kN * kN; ++j) {
                            new_grids[next_new_grid * kN * kN + j] = grid[j];
                            if (grid[j] == 0) {
                                empty_cells[next_new_grid * kN * kN + number_of_empty_cells] = j;
                                number_of_empty_cells++;
                            }
                        }
                        numbers_of_empty_cells[next_new_grid] = number_of_empty_cells;
                    }
                }
                break;
            }
        }

        current_old_grid += number_of_threads;
    }
}

kernel void SudokuSolver(constant int *kGrids, int kNumberOfGrids, constant int *kEmptyCells, int kNumberOfEmptyCells, global int *solved_grid, global int *is_solved) {
    int tid = get_global_id(0);

    int grid[kN * kN];
    for (int i = 0; i < kN * kN; ++i) {
        grid[i] = kGrids[tid * kN *kN + i];
    }

    int current_empty_cell = -1;

    int id = GetNextEmptyCell(kEmptyCells, kNumberOfEmptyCells, current_empty_cell);
    for (int value = 1; value <= kN; ++value) {
        if (IsValid(grid, kN, id, value)) {
            grid[id] = value;
            current_empty_cell++;
            break;
        }
    }

    while ((id = GetNextEmptyCell(kEmptyCells, kNumberOfEmptyCells, current_empty_cell)) != -1) {
        // Another work item solved grid
        if (is_solved == 1) {
            return;
        }

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
                    return;
                }
            }
        }
    }

    *is_solved = 1;

    for (int i = 0; i < kN * kN; ++i) {
        solved_grid[i] = grid[i];
    }
}
