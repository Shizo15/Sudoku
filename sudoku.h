//
// Created by damia on 30.04.2025.
//

#ifndef SUDOKU_H
#define SUDOKU_H

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

bool isSafeInBox(int n, int grid[MAX_SIZE][MAX_SIZE], int rowStart, int colStart, int num);
void fillBox(int n, int grid[MAX_SIZE][MAX_SIZE], int row, int col);
bool isSafeInRow(int n, int grid[MAX_SIZE][MAX_SIZE], int i, int num);
bool isSafeInCol(int n, int grid[MAX_SIZE][MAX_SIZE], int j, int num);
bool checkIfSafe(int n, int grid[MAX_SIZE][MAX_SIZE], int i, int j, int num);
void fillDiagonal(int n, int grid[MAX_SIZE][MAX_SIZE]);
bool fillRemaining(int n, int grid[MAX_SIZE][MAX_SIZE], int i, int j);
void removeKDigits(int n, int grid[MAX_SIZE][MAX_SIZE], int k);
void sudokuGenerator(int n, int grid[MAX_SIZE][MAX_SIZE], int k);
void printBoard(int n, int grid[MAX_SIZE][MAX_SIZE]);
void gameLoop(int n, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]);
bool makeMove(int n, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]);
bool isHintCell(int n, int initialGrid[MAX_SIZE][MAX_SIZE], int row, int col);
bool isBoardComplete(int n, int grid[MAX_SIZE][MAX_SIZE]);
bool isSolutionCorrect(int n, int grid[MAX_SIZE][MAX_SIZE]);


#endif //SUDOKU_H
