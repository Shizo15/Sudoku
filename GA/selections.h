#ifndef SELECTIONS_H
#define SELECTIONS_H

#include "GAconfig.h"

SudokuSolution tournament_selection(SudokuSolution pop[], int tournament_size);
SudokuSolution roulette_selection(SudokuSolution pop[]);
SudokuSolution rank_selection(SudokuSolution pop[]);

#endif