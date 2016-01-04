// kN passed as a build option

typedef struct _stack {
    int array[kN * kN];
    int top;
} stack;

bool empty(stack *s) {
    if (s->top == -1) {
        return true;
    } else {
        return false;
    }
}

void push(stack *s, int v) {
    s->top++;
    s->array[s->top] = v;
}

void pop(stack *s) {
    s->top--;
}

int top(stack *s) {
    return s->array[s->top];
}

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

int GetEmptyCell(int *kGrid, int kSize) {
    int empty_cell = -1;
    for (int i = 0; i < kSize; ++i) {
        if (kGrid[i] == 0) {
            empty_cell = i;
            break;
        }
    }
    return empty_cell;
}

kernel void SudokuSolver(constant int *kGrids, int kNumberOfGrids, global int *solved_grid, global int *is_solved) {
    stack steps;
    steps.top = -1;

    int grid[kN * kN];
    for (int i = 0; i < kN * kN; ++i) {
        grid[i] = kGrids[i];
    }

    int id = GetEmptyCell(grid, kN);
    for (int value = 1; value <= kN; ++value) {
        if (IsValid(grid, kN, id, value)) {
            grid[id] = value;
            push(&steps, id);
            break;
        }
    }

    while ((id = GetEmptyCell(grid, kN * kN)) != -1) {
        // Try to fill an empty cell
        for (int value = 1; value <= kN; ++value) {
            if (IsValid(grid, kN, id, value)) {
                grid[id] = value;
                push(&steps, id);
                break;
            }
        }

        // The cell was not filled
        if (grid[id] == 0) {
            int last_id = id;
            while (grid[last_id] == 0) {
                if (!empty(&steps)) {
                    // Backtrack to the latest filled cell
                    last_id = top(&steps);
                    pop(&steps);

                    // Try to find new value for the latest filled cell
                    int last_value = grid[last_id];
                    grid[last_id] = 0;
                    for (int value = last_value + 1; value <= kN; ++value) {
                        if (IsValid(grid, kN, last_id, value)) {
                            grid[last_id] = value;
                            push(&steps, last_id);
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
