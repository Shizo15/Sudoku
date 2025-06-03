#include "crossovers.h"
#include <stdlib.h>
#include <string.h>

void single_point_crossover(SudokuSolution p1, SudokuSolution p2, SudokuSolution *child) {
    int point = rand() % p1.size;
    for (int i = 0; i < p1.size; i++) {
        for (int j = 0; j < p1.size; j++) {
            child->grid[i][j] = (i < point) ? p1.grid[i][j] : p2.grid[i][j];
        }
    }
    memcpy(child->fixed, p1.fixed, sizeof(int)*MAX_SIZE*MAX_SIZE);
    child->size = p1.size;
    child->subgrid = p1.subgrid;
    child->fitness = -1;
}

void multi_point_crossover(SudokuSolution p1, SudokuSolution p2, SudokuSolution *child) {
    int points[2] = {rand() % p1.size, rand() % p1.size};
    if (points[0] > points[1]) {
        int temp = points[0];
        points[0] = points[1];
        points[1] = temp;
    }

    for (int i = 0; i < p1.size; i++) {
        for (int j = 0; j < p1.size; j++) {
            if (i < points[0]) child->grid[i][j] = p1.grid[i][j];
            else if (i < points[1]) child->grid[i][j] = p2.grid[i][j];
            else child->grid[i][j] = p1.grid[i][j];
        }
    }
    memcpy(child->fixed, p1.fixed, sizeof(int)*MAX_SIZE*MAX_SIZE);
    child->size = p1.size;
    child->subgrid = p1.subgrid;
    child->fitness = -1;
}

void uniform_crossover(SudokuSolution p1, SudokuSolution p2, SudokuSolution *child) {
    for (int i = 0; i < p1.size; i++) {
        for (int j = 0; j < p1.size; j++) {
            if (!p1.fixed[i][j]) {
                child->grid[i][j] = (rand() % 2) ? p1.grid[i][j] : p2.grid[i][j];
            } else {
                child->grid[i][j] = p1.grid[i][j];
            }
        }
    }
    memcpy(child->fixed, p1.fixed, sizeof(int)*MAX_SIZE*MAX_SIZE);
    child->size = p1.size;
    child->subgrid = p1.subgrid;
    child->fitness = -1;
}