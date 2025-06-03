#include "../sudoku.h"
#include "GAconfig.h"

void solveWithGA(int size, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]) {

    SudokuSolution population[POP_SIZE];
    initialize_population(population, initialGrid, size);

    GAConfig config = {
        .selection = SELECT_TOURNAMENT,
        .crossover = CROSS_SINGLE_POINT,
        .tournament_size = 3,
    };

    solve_sudoku_ga(population, config);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = population[0].grid[i][j];
        }
    }
}
