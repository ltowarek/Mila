// n passed as a build option

void ClearBoolArray(bool *array, int array_size) {
    for (int i = 0; i < array_size; ++i) {
        array[i] = false;
    }
}

bool IsValidHorizontally(int *grid, int size, int row) {
    bool is_valid = true;

    bool checked_numbers[n];
    ClearBoolArray(checked_numbers, n);

    for (int column = 0; column < size; ++column) {
        int value = grid[row * size + column];
        if (value != 0) {
             if (checked_numbers[value - 1]) {
                is_valid = false;
                break;
             } else {
                checked_numbers[value - 1] = true;
             }
        }
    }
    return is_valid;
}

bool IsValidVertically(int *grid, int size, int column) {
    bool is_valid = true;

    bool checked_numbers[n];
    ClearBoolArray(checked_numbers, n);

    for (int row = 0; row < size; ++row) {
        int value = grid[row * size + column];
        if (value != 0) {
             if (checked_numbers[value - 1]) {
                is_valid = false;
                break;
             } else {
                checked_numbers[value - 1] = true;
             }
        }
    }
    return is_valid;
}

bool IsValidInBoxes(int *kGrid, int size, int row, int column) {
    int box_size = (int)sqrt((float)size);
    int box_row = row / box_size;
    int box_column = column / box_size;
    bool is_valid = true;

    bool checked_numbers[n];
    ClearBoolArray(checked_numbers, n);

    for (int row = box_row * box_size; row < box_row * box_size + box_size; ++row) {
        for (int column = box_column * box_size; column < box_column * box_size + box_size; ++column) {
            int value = kGrid[row * size + column];
            if (value != 0) {
                 if (checked_numbers[value - 1]) {
                    is_valid = false;
                    break;
                 } else {
                    checked_numbers[value - 1] = true;
                 }
            }
        }
    }
    return is_valid;
}

bool IsValid(int *grid, int size, int id) {
    int row = id / size;
    int column = id % size;
    return grid[id] >= 1 &&
           grid[id] <= size &&
           IsValidHorizontally(grid, size, row) &&
           IsValidVertically(grid, size, column) &&
           IsValidInBoxes(grid, size, row, column);
}

void PrintGrid(int *grid, int size) {
    printf("grid: ");
    for (int i = 0; i < size; ++i) {
        printf("%d, ", grid[i]);
    }
    printf("\n");
}

kernel void SudokuSolverBFS(global int *old_grids, global int *number_of_old_grids, global int *new_grids, global int *number_of_new_grids, global int *empty_cells, global int *numbers_of_empty_cells) {
    int tid = get_global_id(0);
    int number_of_threads = get_global_size(0);
    int current_old_grid = tid;

    // Iterate over all old grids
    while (current_old_grid < *number_of_old_grids) {
        // Get next grid
        int grid[n * n];
        for (int i = 0; i < n * n; ++i) {
            grid[i] = old_grids[current_old_grid * n * n + i];
        }

        for (int i = 0; i < n * n; ++i) {
            // Find first empty cell
            if (grid[i] == 0) {
                // Fill this cell with all valid values
                for (int value = 1; value <= n; ++value) {
                    grid[i] = value;
                    if (IsValid(grid, n, i)) {
                        int next_new_grid = atomic_inc(number_of_new_grids);
                        int number_of_empty_cells = 0;
                        for (int j = 0; j < n * n; ++j) {
                            new_grids[next_new_grid * n * n + j] = grid[j];
                            if (grid[j] == 0) {
                                empty_cells[next_new_grid * n * n + number_of_empty_cells] = j;
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

kernel void SudokuSolverDFS(global int *grids, global int *number_of_grids, global int *empty_cells, global int *numbers_of_empty_cells, global int *solved_grid, global int *is_solved) {
    int number_of_threads = get_global_size(0);
    int current_grid[n * n];
    int current_grid_id = get_global_id(0);
    int current_empty_cells[n * n];
    int current_empty_cell_id = 0;
    int number_of_empty_cells = 0;

    while ((*is_solved == 0) && (current_grid_id < *number_of_grids)) {
        for (int i = 0; i < n * n; ++i) {
            current_grid[i] = grids[current_grid_id * n * n + i];
            current_empty_cells[i] = empty_cells[current_grid_id * n * n + i];
        }

        current_empty_cell_id = 0;
        number_of_empty_cells = numbers_of_empty_cells[current_grid_id];

        while ((current_empty_cell_id >= 0) && (current_empty_cell_id < number_of_empty_cells)) {
            int id = current_empty_cells[current_empty_cell_id];
            current_grid[id]++;
            if (IsValid(current_grid, n, id)) {
                current_empty_cell_id++;
            } else if (current_grid[id] >= n) {
                current_grid[id] = 0;
                current_empty_cell_id--;
            }
        }

        if (current_empty_cell_id == number_of_empty_cells) {
            // Only one thread will update solved_grid
            if (!atomic_inc(is_solved)) {
                for (int i = 0; i < n * n; ++i) {
                    solved_grid[i] = current_grid[i];
                }
            }
        }

        current_grid_id += number_of_threads;
    }
}
