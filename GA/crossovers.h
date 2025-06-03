#ifndef CROSSOVERS_H
#define CROSSOVERS_H

#include "GAconfig.h"

void single_point_crossover(SudokuSolution p1, SudokuSolution p2, SudokuSolution *child);
void multi_point_crossover(SudokuSolution p1, SudokuSolution p2, SudokuSolution *child);
void uniform_crossover(SudokuSolution p1, SudokuSolution p2, SudokuSolution *child);

#endif