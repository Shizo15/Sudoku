#include "mutations.h"
#include <stdlib.h>

void mutate(SudokuSolution *sol) {
    if (sol->size <= 0 || sol->subgrid <= 0) return;

    // choosing random subgrid
    int boxRow = (rand() % (sol->size/sol->subgrid)) * sol->subgrid;
    int boxCol = (rand() % (sol->size/sol->subgrid)) * sol->subgrid;

    int row1, col1, row2, col2;
    int attempts = 0;

    //looking for two changeable cells
    do {
        row1 = boxRow + rand() % sol->subgrid;
        col1 = boxCol + rand() % sol->subgrid;
        attempts++;
    } while (sol->fixed[row1][col1] && attempts < 100);

    attempts = 0;
    do {
        row2 = boxRow + rand() % sol->subgrid;
        col2 = boxCol + rand() % sol->subgrid;
        attempts++;
    } while ((sol->fixed[row2][col2] || (row1 == row2 && col1 == col2)) && attempts < 100);

    // if both cells are changeable - swapping them
    if (!sol->fixed[row1][col1] && !sol->fixed[row2][col2]) {
        int temp = sol->grid[row1][col1];
        sol->grid[row1][col1] = sol->grid[row2][col2];
        sol->grid[row2][col2] = temp;
    }
}