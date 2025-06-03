#include "GAconfig.h"
#include "selections.h"
#include "crossovers.h"
#include "mutations.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void initialize_population(SudokuSolution pop[], int puzzle[MAX_SIZE][MAX_SIZE], int size) {
    int subgrid = (int)sqrt(size);

    for (int p = 0; p < POP_SIZE; p++) {
        pop[p].size = size;
        pop[p].subgrid = subgrid;

        // copy initial board
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                pop[p].grid[i][j] = puzzle[i][j];
                pop[p].fixed[i][j] = puzzle[i][j];
            }
        }

        // fill subgrids with random numbers
        for (int boxRow = 0; boxRow < size; boxRow += subgrid) {
            for (int boxCol = 0; boxCol < size; boxCol += subgrid) {
                int used[MAX_SIZE+1] = {0};

                for (int i = 0; i < subgrid; i++) {
                    for (int j = 0; j < subgrid; j++) {
                        int val = pop[p].grid[boxRow+i][boxCol+j];
                        if (val != 0) {
                            used[val] = 1;
                        }
                    }
                }

                // insert missing nimbers randomly
                for (int i = 0; i < subgrid; i++) {
                    for (int j = 0; j < subgrid; j++) {
                        if (pop[p].grid[boxRow+i][boxCol+j] == 0) {
                            int num;
                            do {
                                num = 1 + rand() % size;
                            } while (used[num]);
                            pop[p].grid[boxRow+i][boxCol+j] = num;
                            used[num] = 1;
                        }
                    }
                }
            }
        }
    }
}


void calculate_fitness(SudokuSolution *sol) {
    int errors = 0;
    int size = sol->size;
    int subgrid = sol->subgrid;

    // check rows and cols
    for (int i = 0; i < size; i++) {
        int row[MAX_SIZE+1] = {0};
        int col[MAX_SIZE+1] = {0};

        for (int j = 0; j < size; j++) {
            row[sol->grid[i][j]]++;
            col[sol->grid[j][i]]++;
        }

        for (int n = 1; n <= size; n++) {
            if (row[n] > 1) errors += row[n] - 1;
            if (col[n] > 1) errors += col[n] - 1;
        }
    }

    // checking subgrids
    for (int boxRow = 0; boxRow < size; boxRow += subgrid) {
        for (int boxCol = 0; boxCol < size; boxCol += subgrid) {
            int count[MAX_SIZE+1] = {0};

            for (int i = 0; i < subgrid; i++) {
                for (int j = 0; j < subgrid; j++) {
                    int val = sol->grid[boxRow+i][boxCol+j];
                    count[val]++;
                }
            }

            for (int n = 1; n <= size; n++) {
                if (count[n] > 1) errors += count[n] - 1;
            }
        }
    }

    sol->fitness = errors;
}


void solve_sudoku_ga(SudokuSolution population[], GAConfig config) {
    for (int gen = 0; gen < MAX_GEN; gen++) {

        //calculate fitness
        for (int i = 0; i < POP_SIZE; i++) {
            calculate_fitness(&population[i]);
        }

        // sorting population (best on top)
        for (int i = 0; i < POP_SIZE - 1; i++) {
            for (int j = i + 1; j < POP_SIZE; j++) {
                if (population[i].fitness > population[j].fitness) {
                    SudokuSolution temp = population[i];
                    population[i] = population[j];
                    population[j] = temp;
                }
            }
        }

        printf("Generation %d: best result = %d\n", gen, population[0].fitness);

        // end if optimal solution - 0
        if (population[0].fitness == 0) {
            printf("Solution found in generation %d!\n", gen);
            break;
        }

        SudokuSolution new_pop[POP_SIZE];

        // copy elite
        for (int i = 0; i < ELITE_COUNT; i++) {
            new_pop[i] = population[i];
        }

        for (int i = ELITE_COUNT; i < POP_SIZE; i++) {
            SudokuSolution parent1, parent2;

            //choosing parents
            if (config.selection == SELECT_ROULETTE) {
                parent1 = roulette_selection(population);
                parent2 = roulette_selection(population);
            } else if (config.selection == SELECT_RANKING) {
                parent1 = rank_selection(population);
                parent2 = rank_selection(population);
            } else {
                parent1 = tournament_selection(population, config.tournament_size);
                parent2 = tournament_selection(population, config.tournament_size);
            }

            // crossover
            if (config.crossover == CROSS_MULTI_POINT) {
                multi_point_crossover(parent1, parent2, &new_pop[i]);
            } else if (config.crossover == CROSS_UNIFORM) {
                uniform_crossover(parent1, parent2, &new_pop[i]);
            } else {
                single_point_crossover(parent1, parent2, &new_pop[i]);
            }

            // mutation
            if ((double)rand() / RAND_MAX < MUTATION_RATE) {
                mutate(&new_pop[i]);
            }
        }

        // replace old popul with new
        memcpy(population, new_pop, sizeof(SudokuSolution) * POP_SIZE);
    }
}
