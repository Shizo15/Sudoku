#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "sudoku.h"

void clearConsole() {
    // Optional: Uncomment if console clearing is needed
    // #ifdef _WIN32
    //     system("cls");
    // #else
    //     system("clear");
    // #endif
    fflush(stdout);
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

void startNewGame() {
    while (true) {
        int boardSize = selectBoardSize();
        if (boardSize <= 0) return;

        int difficulty = selectDifficulty();
        if (difficulty <= 0) continue;

        int k;
        int total = boardSize * boardSize;

        switch (difficulty) {
        case 1: k = total - (total * 3 / 4); break; // Easy - 75% filled
        case 2: k = total - (total / 2);     break; // Medium - 50% filled
        case 3: k = total - (total / 4);     break; // Hard - 25% filled
        default: k = total - (total / 2);    break;
        }


        int grid[MAX_SIZE][MAX_SIZE] = {0};
        int initialGrid[MAX_SIZE][MAX_SIZE] = {0};

        sudokuGenerator(boardSize, grid, k);
        memcpy(initialGrid, grid, sizeof(int) * MAX_SIZE * MAX_SIZE);

        gameLoop(boardSize, grid, initialGrid);
        return;
    }
}

//Returns true if cell is hint from the original generated board
bool isHintCell(int n, int initialGrid[MAX_SIZE][MAX_SIZE], int row, int col) {
    return initialGrid[row][col] != 0;
}

bool makeMove(int n, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]) {
    int row, col, num;
    printf("Enter row, column and value (1-%d) or 0 to clear: ", n);
    fflush(stdout);

    if (scanf("%d %d %d", &row, &col, &num) != 3) {
        clearInputBuffer();
        printf("Invalid input format. Please try again.\n");
        return false;
    }

    if (row < 1 || row > n || col < 1 || col > n || num < 0 || num > n) {
        printf("Invalid input values. Try again.\n");
        clearInputBuffer();
        return false;
    }

    row--;
    col--;

    if (isHintCell(n, initialGrid, row, col)) {
        printf("Cannot modify hint cells!\n");
        clearInputBuffer();
        return false;
    }

    grid[row][col] = num;
    clearInputBuffer();
    return true;
}

void gameLoop(int n, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]) {
    time_t startTime = time(NULL);
    int choice;
    bool gameRunning = true;

    while (gameRunning) {
        clearConsole();
        printf("\n=== SUDOKU GAME ===\n");
        printf("Size: %dx%d\n", n, n);
        printBoard(n, grid);

        if (isBoardComplete(n, grid)) {
            if (isSolutionCorrect(n, grid)) {
                printf("\nCongratulations! You solved the Sudoku!\n");
                time_t endTime = time(NULL);
                printf("Time taken: %.0f seconds\n", difftime(endTime, startTime));
                printf("\nPress Enter to continue...");
                clearInputBuffer();
                getchar();
                return;
            } else {
                printf("\nSome cells are incorrect. Keep trying.\n");
                continue;
            }
        }

        printGameMenu();
        printf("Your choice: ");
        fflush(stdout);

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                if (!makeMove(n, grid, initialGrid)) {
                    printf("Invalid move. Try again.\n");
                }
                break;
            case 2:
                saveGame(n, grid, initialGrid);
                break;
            case 3:
                printInstructions();
                break;
            case 4:
                solveWithSA(n, grid, initialGrid);
                break;
            case 5:
                solveWithGA(n, grid, initialGrid);
                break;
            case 6:
                gameRunning = false;
                break;
            default:
                printf("Invalid choice. Please select 1-6.\n");
        }

        if (choice != 1) {
            printf("Press Enter to continue...");
            clearInputBuffer();
            getchar();
        }
    }
}

void saveGame(int size, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]) {
    FILE* file = fopen("sudoku_save.txt", "w");
    if (!file) {
        printf("Failed to save game!\n");
        return;
    }

    fprintf(file, "%d\n", size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            fprintf(file, "%d%c", grid[i][j], (j == size - 1) ? '\n' : ' ');

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            fprintf(file, "%d%c", initialGrid[i][j], (j == size - 1) ? '\n' : ' ');

    fclose(file);
    printf("Game saved successfully.\n");
}

bool loadGame(int *size, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]) {
    FILE* file = fopen("sudoku_save.txt", "r");
    if (!file) {
        printf("No saved game found.\n");
        return false;
    }

    if (fscanf(file, "%d", size) != 1) {
        fclose(file);
        return false;
    }

    for (int i = 0; i < *size; i++)
        for (int j = 0; j < *size; j++)
            if (fscanf(file, "%d", &grid[i][j]) != 1) {
                fclose(file);
                return false;
            }

    for (int i = 0; i < *size; i++)
        for (int j = 0; j < *size; j++)
            if (fscanf(file, "%d", &initialGrid[i][j]) != 1) {
                fclose(file);
                return false;
            }

    fclose(file);
    printf("Game loaded successfully.\n");
    return true;
}

void removeKDigits(int n, int grid[MAX_SIZE][MAX_SIZE], int k) {
    while (k > 0) {
        int i = rand() % n;
        int j = rand() % n;
        if (grid[i][j] != 0) {
            grid[i][j] = 0;
            k--;
        }
    }
}


void swapRowsGeneral(int n, int grid[MAX_SIZE][MAX_SIZE], int row1, int row2) {
    for (int i = 0; i < n; i++) {
        int temp = grid[row1][i];
        grid[row1][i] = grid[row2][i];
        grid[row2][i] = temp;
    }
}

void swapColsGeneral(int n, int grid[MAX_SIZE][MAX_SIZE], int col1, int col2) {
    for (int i = 0; i < n; i++) {
        int temp = grid[i][col1];
        grid[i][col1] = grid[i][col2];
        grid[i][col2] = temp;
    }
}

void swapNumbersGeneral(int n, int grid[MAX_SIZE][MAX_SIZE], int n1, int n2) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == n1) grid[i][j] = n2;
            else if (grid[i][j] == n2) grid[i][j] = n1;
        }
}

void applyRandomTransformations(int n, int grid[MAX_SIZE][MAX_SIZE]) {
    int square = (int)sqrt(n);
    for (int i = 0; i < 10; i++) {
        int block = rand() % square;
        int row1 = block * square + rand() % square;
        int row2 = block * square + rand() % square;
        if (row1 != row2) swapRowsGeneral(n, grid, row1, row2);

        int col1 = block * square + rand() % square;
        int col2 = block * square + rand() % square;
        if (col1 != col2) swapColsGeneral(n, grid, col1, col2);

        int n1 = 1 + rand() % n;
        int n2 = 1 + rand() % n;
        if (n1 != n2) swapNumbersGeneral(n, grid, n1, n2);
    }
}


void sudokuGenerator(int n, int grid[MAX_SIZE][MAX_SIZE], int k) {
    memset(grid, 0, sizeof(int) * MAX_SIZE * MAX_SIZE);

    if (n == 4) {
        int base[4][4] = {
            {1, 2, 3, 4},
            {3, 4, 1, 2},
            {2, 1, 4, 3},
            {4, 3, 2, 1}
        };
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                grid[i][j] = base[i][j];
    } else if (n == 9) {
        int base[9][9] = {
            {1,2,3,4,5,6,7,8,9},
            {4,5,6,7,8,9,1,2,3},
            {7,8,9,1,2,3,4,5,6},
            {2,3,4,5,6,7,8,9,1},
            {5,6,7,8,9,1,2,3,4},
            {8,9,1,2,3,4,5,6,7},
            {3,4,5,6,7,8,9,1,2},
            {6,7,8,9,1,2,3,4,5},
            {9,1,2,3,4,5,6,7,8}
        };
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                grid[i][j] = base[i][j];
    } else if (n == 16) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                grid[i][j] = (i * 4 + i / 4 + j) % 16 + 1;
    } else {
        printf("Unsupported board size.\n");
        return;
    }

    applyRandomTransformations(n, grid);
    removeKDigits(n, grid, k);
}

void printBoard(int n, int grid[MAX_SIZE][MAX_SIZE]) {
    int square = (int)sqrt(n);
    int emptyCount = 0;
    printf("\n");

    for (int i = 0; i < n; i++) {
        if (i % square == 0 && i != 0) {
            for (int j = 0; j < n; j++) {
                printf("---");
                if (j % square == square - 1 && j != n - 1)
                    printf("-");
            }
            printf("\n");
        }

        for (int j = 0; j < n; j++) {
            if (j % square == 0 && j != 0) printf("| ");
            if (grid[i][j] == 0) {
                printf(" . ");
                emptyCount++;
            } else {
                printf("%2d ", grid[i][j]);
            }
        }
        printf("\n");
    }
    printf("\nEmpty cells: %d\n", emptyCount);
}

bool isBoardComplete(int n, int grid[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == 0)
                return false;
    return true;
}

bool isSolutionCorrect(int n, int grid[MAX_SIZE][MAX_SIZE]) {
    if (!isBoardComplete(n, grid)) return false;
    int square = (int)sqrt(n);

    for (int i = 0; i < n; i++) {
        bool *rowCheck = calloc(n+1, sizeof(bool));
        bool *colCheck = calloc(n+1, sizeof(bool));
        if (!rowCheck || !colCheck) return false;

        for (int j = 0; j < n; j++) {
            int rowVal = grid[i][j];
            int colVal = grid[j][i];

            if (rowVal < 1 || rowVal > n || rowCheck[rowVal]) return false;
            if (colVal < 1 || colVal > n || colCheck[colVal]) return false;

            rowCheck[rowVal] = true;
            colCheck[colVal] = true;
        }
        free(rowCheck);
        free(colCheck);
    }

    for (int boxRow = 0; boxRow < n; boxRow += square) {
        for (int boxCol = 0; boxCol < n; boxCol += square) {
            bool *boxCheck = calloc(n+1, sizeof(bool));
            if (!boxCheck) return false;

            for (int i = 0; i < square; i++) {
                for (int j = 0; j < square; j++) {
                    int val = grid[boxRow + i][boxCol + j];
                    if (val < 1 || val > n || boxCheck[val]) return false;
                    boxCheck[val] = true;
                }
            }
            free(boxCheck);
        }
    }

    return true;
}

int main() {
    srand(time(0));
    printMainMenu();
    return 0;
}
