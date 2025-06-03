#ifndef GACONFIG_H
#define GACONFIG_H

#include <stdbool.h>
#include <math.h>

#define MAX_SIZE 16
#define POP_SIZE 50
#define MAX_GEN 1000
#define MUTATION_RATE 0.1
#define ELITE_COUNT 1

typedef struct {
    int grid[MAX_SIZE][MAX_SIZE];
    int fixed[MAX_SIZE][MAX_SIZE];
    int fitness;
    int size;
    int subgrid;
} SudokuSolution;

typedef enum {
    SELECT_TOURNAMENT,
    SELECT_ROULETTE,
    SELECT_RANKING
} SelectionMethod;

typedef enum {
    CROSS_SINGLE_POINT,
    CROSS_MULTI_POINT,
    CROSS_UNIFORM
} CrossoverMethod;

typedef struct {
    SelectionMethod selection;
    CrossoverMethod crossover;
    int tournament_size;
} GAConfig;

void initialize_population(SudokuSolution pop[], int puzzle[MAX_SIZE][MAX_SIZE], int size);
void calculate_fitness(SudokuSolution *sol);
void solve_sudoku_ga(SudokuSolution population[], GAConfig config);

#endif