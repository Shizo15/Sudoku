#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdbool.h>
#define MAX_SIZE 16

// Function declarations
void clearInputBuffer();
int selectBoardSize();
int selectDifficulty();
void printInstructions();
void startNewGame();
void saveGame(int size, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]);
bool loadGame(int *size, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]);
void printMainMenu();
void printGameMenu();
void clearConsole();


void removeKDigits(int n, int grid[MAX_SIZE][MAX_SIZE], int k);
void sudokuGenerator(int n, int grid[MAX_SIZE][MAX_SIZE], int k);
void printBoard(int n, int grid[MAX_SIZE][MAX_SIZE]);
void gameLoop(int n, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]);
bool makeMove(int n, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]);
bool isHintCell(int n, int initialGrid[MAX_SIZE][MAX_SIZE], int row, int col);
bool isBoardComplete(int n, int grid[MAX_SIZE][MAX_SIZE]);
bool isSolutionCorrect(int n, int grid[MAX_SIZE][MAX_SIZE]);

void swapRowsGeneral(int n, int grid[MAX_SIZE][MAX_SIZE], int row1, int row2);
void swapColsGeneral(int n, int grid[MAX_SIZE][MAX_SIZE], int col1, int col2);
void swapNumbersGeneral(int n, int grid[MAX_SIZE][MAX_SIZE], int n1, int n2);
void applyRandomTransformations(int n, int grid[MAX_SIZE][MAX_SIZE]);

void solveWithSA(int n, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]);

void solveWithGA(int size, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]);

#endif
