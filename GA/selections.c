#include "selections.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// best from few random
SudokuSolution tournament_selection(SudokuSolution pop[], int t_size) {
    SudokuSolution best = pop[rand() % POP_SIZE];

    for (int i = 1; i < t_size; i++) {
        SudokuSolution current = pop[rand() % POP_SIZE];
        if (current.fitness < best.fitness) {
            best = current;
        }
    }
    return best;
}

// better fitness - bigger chance
SudokuSolution roulette_selection(SudokuSolution pop[]) {
    double total = 0;
    for (int i = 0; i < POP_SIZE; i++) {
        total += 1.0 / (1 + pop[i].fitness);
    }

    double r = ((double)rand() / RAND_MAX) * total;
    double sum = 0;

    for (int i = 0; i < POP_SIZE; i++) {
        sum += 1.0 / (1 + pop[i].fitness);
        if (sum >= r) return pop[i];
    }

    return pop[POP_SIZE - 1]; // zapasowo
}

// better finess - higher in rank
SudokuSolution rank_selection(SudokuSolution pop[]) {
    SudokuSolution sorted[POP_SIZE];
    memcpy(sorted, pop, sizeof(sorted));

    for (int i = 0; i < POP_SIZE - 1; i++) {
        for (int j = i + 1; j < POP_SIZE; j++) {
            if (sorted[i].fitness > sorted[j].fitness) {
                SudokuSolution temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }

    int index = (int)(POP_SIZE * (1.0 - sqrt((double)rand() / RAND_MAX)));
    return sorted[index];
}
