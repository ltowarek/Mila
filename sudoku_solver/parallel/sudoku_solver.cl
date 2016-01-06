// kN passed as a build option

void ClearBoolArray(bool *array, int array_size, bool value) {
    for (int i = 0; i < array_size; ++i) {
        array[i] = value;
    }
}

bool IsValidHorizontally(int *kGrid, int kSize, int kRow) {
    bool is_valid = true;

    bool checked_numbers[kN];
    ClearBoolArray(checked_numbers, kN, false);

    for (int column = 0; column < kSize; ++column) {
        int value = kGrid[kRow * kSize + column];
        if (value != 0 && checked_numbers[value - 1]) {
            is_valid = false;
            break;
        } else {
            checked_numbers[value - 1] = true;
        }
    }
    return is_valid;
}

bool IsValidVertically(int *kGrid, int kSize, int kColumn) {
    bool is_valid = true;

    bool checked_numbers[kN];
    ClearBoolArray(checked_numbers, kN, false);

    for (int row = 0; row < kSize; ++row) {
        int value = kGrid[row * kSize + kColumn];
        if (value != 0 && checked_numbers[value - 1]) {
            is_valid = false;
            break;
        } else {
            checked_numbers[value - 1] = true;
        }
    }
    return is_valid;
}

bool IsValidInBoxes(int *kGrid, int kSize, int kRow, int kColumn) {
    int kBoxSize = (int)sqrt((float)kSize);
    int kBoxRow = kRow / kBoxSize;
    int kBoxColumn = kColumn / kBoxSize;
    bool is_valid = true;

    bool checked_numbers[kN];
    ClearBoolArray(checked_numbers, kN, false);

    for (int row = kBoxRow * kBoxSize; row < kBoxRow * kBoxSize + kBoxSize; ++row) {
        for (int column = kBoxColumn * kBoxSize; column < kBoxColumn * kBoxSize + kBoxSize; ++column) {
            int value = kGrid[row * kSize + column];
            if (value != 0 && checked_numbers[value - 1]) {
                is_valid = false;
                break;
            } else {
                checked_numbers[value - 1] = true;
            }
        }
    }
    return is_valid;
}

bool IsValid(int *kGrid, int kSize, int kId) {
    int kRow = kId / kSize;
    int kColumn = kId % kSize;
    return kGrid[kId] >= 1 &&
           kGrid[kId] <= kSize &&
           IsValidHorizontally(kGrid, kSize, kRow) &&
           IsValidVertically(kGrid, kSize, kColumn) &&
           IsValidInBoxes(kGrid, kSize, kRow, kColumn);
}

kernel void SudokuSolverBFS(constant int *kOldGrids, global int *number_of_old_grids, global int *new_grids, global int *number_of_new_grids, global int *empty_cells, global int *numbers_of_empty_cells) {
    int tid = get_global_id(0);
    int number_of_threads = get_global_size(0);
    int current_old_grid = tid;

    // Iterate over all old grids
    while (current_old_grid < *number_of_old_grids) {
        // Get next grid
        int grid[kN * kN];
        for (int i = 0; i < kN * kN; ++i) {
            grid[i] = kOldGrids[current_old_grid * kN * kN + i];
        }

        for (int i = 0; i < kN * kN; ++i) {
            // Find first empty cell
            if (grid[i] == 0) {
                // Fill this cell with all valid values
                for (int value = 1; value <= kN; ++value) {
                    grid[i] = value;
                    if (IsValid(grid, kN, i)) {
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

kernel void SudokuSolverDFS(constant int *kGrids, global int *number_of_grids, constant int *kEmptyCells, constant int *kNumbersOfEmptyCells, global int *solved_grid, global int *is_solved) {
    int tid = get_global_id(0);
    int number_of_threads = get_global_size(0);
    int current_grid = tid;

    while ((*is_solved == 0) && (current_grid < *number_of_grids)) {
        int grid[kN * kN];
        int empty_cells[kN * kN];
        for (int i = 0; i < kN * kN; ++i) {
            grid[i] = kGrids[current_grid * kN *kN + i];
            empty_cells[i] = kEmptyCells[current_grid * kN *kN + i];
        }

        int current_empty_cell = 0;
        int number_of_empty_cells = kNumbersOfEmptyCells[current_grid];

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
            // Only one thread will update solved_grid
            if (!atomic_inc(is_solved)) {
                for (int i = 0; i < kN * kN; ++i) {
                    solved_grid[i] = grid[i];
                }
            }
        }

        current_grid += number_of_threads;
    }
}
