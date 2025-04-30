#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "sudoku.h"

//Clears the console (commented bcs sometimes causing problems with display)
void clearConsole() {
// #ifdef _WIN32
//     system("cls");
// #else
//     system("clear");
// #endif
//     fflush(stdout);
}

//Empty input buffer
void clearInputBuffer() {
    while (getchar() != '\n');
}

//Menu for selecting board size
int selectBoardSize() {
    int sizeChoice;
    do {
        printf("\nChoose board size:\n");
        printf("1. 4x4\n");
        printf("2. 9x9\n");
        printf("3. 16x16\n");
        printf("4. Back to main menu\n");
        printf("Your choice: ");

        if (scanf("%d", &sizeChoice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (sizeChoice) {
            case 1:
                return 4;
            case 2:
                return 9;
            case 3:
                return 16;
            case 4:
                return -1;
            default:
                printf("Invalid choice. Please select 1-4.\n");
        }
    } while (true);
}

//Menu for selecting difficulty
int selectDifficulty() {
    int difficultyChoice;
    do {
        printf("\nSelect difficulty:\n");
        printf("1. Easy (many hints)\n");
        printf("2. Medium (some hints)\n");
        printf("3. Hard (few hints)\n");
        printf("4. Back\n");
        printf("Your choice: ");

        if (scanf("%d", &difficultyChoice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (difficultyChoice) {
            case 1:
                return 1;
            case 2:
                return 2;
            case 3:
                return 3;
            case 4:
                return -1;
            default:
                printf("Invalid choice. Please select 1-4.\n");
        }
    } while (true);
}

void printInstructions() {
    clearConsole();
    printf("\n=== SUDOKU INSTRUCTIONS ===\n");
    printf("1. Fill the grid so that every row, column and box\n");
    printf("   contains all digits from 1 to N (where N is grid size)\n");
    printf("2. To make a move, enter row, column and value\n");
    printf("3. To remove a value, enter 0 as value\n");
    printf("4. Some cells are pre-filled (hints) - you can't change them\n");
    printf("\nPress Enter to continue...");
    clearInputBuffer();
    getchar();
}

void startNewGame() {

    while (true)
    {
        int boardSize = selectBoardSize();
        if (boardSize <= 0) return;

        int difficulty = selectDifficulty();
        if (difficulty <= 0) continue;


        // Calculate number of cells to remove based on difficulty
        int k;
        switch (difficulty) {
            case 1:
                k = boardSize * boardSize / 3;
                break;  // Easy
            case 2:
                k = boardSize * boardSize / 2;
                break;  // Medium
            case 3:
                k = boardSize * boardSize * 2 / 3;
                break;  // Hard
            default:
                k = boardSize * boardSize / 2;
                break;
        }

        // Allocate grids
        int grid[MAX_SIZE][MAX_SIZE] = {0};
        int initialGrid[MAX_SIZE][MAX_SIZE] = {0};

        // Generate Sudoku puzzle and store initial state
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

//Reads user move input and validates it
bool makeMove(int n, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]) {
    int row, col, num;

    printf("Enter row, column and value (1-%d) or 0 to clear: ", n);
    fflush(stdout);

    if (scanf("%d %d %d", &row, &col, &num) != 3) {
        clearInputBuffer();
        printf("Invalid input format. Please try again.\n");
        return false;
    }

    // Validate input
    if (row < 1 || row > n || col < 1 || col > n) {
        printf("Row and column must be between 1 and %d.\n", n);
        clearInputBuffer();
        return false;
    }

    if (num < 0 || num > n) {
        printf("Value must be between 0 and %d.\n", n);
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

//Main game loop which handles user interaction and game state
void gameLoop(int n, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]) {
    time_t startTime = time(NULL); // tracking time taken to solve

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
                gameRunning = false;
                break;
            default:
                printf("Invalid choice. Please select 1-4.\n");
        }

        // Pause to let user see messages
        if (choice != 1) {
            printf("Press Enter to continue...");
            clearInputBuffer();
            getchar();
        }
    }
}

//Saves current initial board and game state to file
void saveGame(int size, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]) {
    FILE* file = fopen("sudoku_save.txt", "w");
    if (!file) {
        printf("Failed to save game!\n");
        return;
    }

    // Write size first
    fprintf(file, "%d\n", size);

    // Write current grid
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(file, "%d ", grid[i][j]);
        }
        fprintf(file, "\n");
    }

    // Write initial grid
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(file, "%d ", initialGrid[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Game saved successfully.\n");
}

//Loads saved game state from file
bool loadGame(int *size, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]) {
    FILE* file = fopen("sudoku_save.txt", "r");
    if (!file) {
        printf("No saved game found.\n");
        return false;
    }

    // Read size first
    if (fscanf(file, "%d", size) != 1) {
        printf("Failed to read game size.\n");
        fclose(file);
        return false;
    }

    // Read current grid
    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            if (fscanf(file, "%d", &grid[i][j]) != 1) {
                printf("Failed to read grid data.\n");
                fclose(file);
                return false;
            }
        }
    }

    // Read initial grid
    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            if (fscanf(file, "%d", &initialGrid[i][j]) != 1) {
                printf("Failed to read initial grid data.\n");
                fclose(file);
                return false;
            }
        }
    }

    fclose(file);
    printf("Game loaded successfully.\n");
    return true;
}

//Draws main menu and responds to user sekection
void printMainMenu() {
    int choice;
    do {
        clearConsole();
        printf("\n=== SUDOKU GAME ===\n");
        printf("1. New Game\n");
        printf("2. Load Game\n");
        printf("3. Instructions\n");
        printf("4. Exit\n");
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input.\n");
            continue;
        }

        switch (choice) {
            case 1:
                startNewGame();
                break;
            case 2: {
                int size;
                int grid[MAX_SIZE][MAX_SIZE] = {0};
                int initialGrid[MAX_SIZE][MAX_SIZE] = {0};
                if (loadGame(&size, grid, initialGrid)) {
                    gameLoop(size, grid, initialGrid);
                } else {
                    printf("Press Enter to continue...");
                    clearInputBuffer();
                    getchar();
                }
                break;
            }
            case 3:
                printInstructions();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    } while (true);
}

//In-game menu to handle plyer moves
void printGameMenu() {
    printf("\n=== GAME MENU ===\n");
    printf("1. Make a move\n");
    printf("2. Save game\n");
    printf("3. Show instructions\n");
    printf("4. Back to main menu\n");
}

//Check if number is unique in sub-box
bool isSafeInBox(int n, int grid[MAX_SIZE][MAX_SIZE], int rowStart, int colStart, int num) {
    int square = (int)sqrt(n);
    for (int i = 0; i < square; i++) {
        for (int j = 0; j < square; j++) {
            if (grid[rowStart + i][colStart + j] == num) {
                return false;
            }
        }
    }
    return true;
}

//Randomly fill one sub-grid
void fillBox(int n, int grid[MAX_SIZE][MAX_SIZE], int row, int col) {
    int square = (int)sqrt(n);
    int max_num = n;

    for (int i = 0; i < square; i++) {
        for (int j = 0; j < square; j++) {
            int num;
            int attempts = 0;
            do {
                num = (rand() % max_num) + 1;
                attempts++;
                // Prevent infinite loops with small grids
                if (attempts > max_num * 2) {
                    // Reset the box if stuck
                    for (int x = 0; x < square; x++) {
                        for (int y = 0; y < square; y++) {
                            grid[row + x][col + y] = 0;
                        }
                    }
                    attempts = 0;
                }
            } while (!isSafeInBox(n, grid, row, col, num));
            grid[row + i][col + j] = num;
        }
    }
}

bool isSafeInRow(int n, int grid[MAX_SIZE][MAX_SIZE], int i, int num) {
    for (int j = 0; j < n; j++) {
        if (grid[i][j] == num) {
            return false;
        }
    }
    return true;
}

bool isSafeInCol(int n, int grid[MAX_SIZE][MAX_SIZE], int j, int num) {
    for (int i = 0; i < n; i++) {
        if (grid[i][j] == num) {
            return false;
        }
    }
    return true;
}

bool checkIfSafe(int n, int grid[MAX_SIZE][MAX_SIZE], int i, int j, int num) {
    int square = (int)sqrt(n);
    return isSafeInRow(n, grid, i, num) &&
           isSafeInCol(n, grid, j, num) &&
           isSafeInBox(n, grid, i - i % square, j - j % square, num);
}

//Fill diagonal boxes first to simplify generation
void fillDiagonal(int n, int grid[MAX_SIZE][MAX_SIZE]) {
    int square = (int)sqrt(n);
    for (int i = 0; i < n; i += square) {
        fillBox(n, grid, i, i);
    }
}

//Filling rest of the board
bool fillRemaining(int n, int grid[MAX_SIZE][MAX_SIZE], int i, int j) {
    if (i == n) {
        return true;
    }
    if (j == n) {
        return fillRemaining(n, grid, i + 1, 0);
    }
    if (grid[i][j] != 0) {
        return fillRemaining(n, grid, i, j + 1);
    }

    for (int num = 1; num <= n; num++) {
        if (checkIfSafe(n, grid, i, j, num)) {
            grid[i][j] = num;
            if (fillRemaining(n, grid, i, j + 1)) {
                return true;
            }
            grid[i][j] = 0;
        }
    }
    return false;
}

//Randomly clears k cells from the generated board
void removeKDigits(int n, int grid[MAX_SIZE][MAX_SIZE], int k) {
    while (k > 0) {
        int cellId = rand() % (n * n);
        int i = cellId / n;
        int j = cellId % n;

        if (grid[i][j] != 0) {
            grid[i][j] = 0;
            k--;
        }
    }
}

void sudokuGenerator(int n, int grid[MAX_SIZE][MAX_SIZE], int k) {
    // Initialize grid with 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = 0;
        }
    }

    fillDiagonal(n, grid);

    // Verify the grid was filled correctly
    if (!fillRemaining(n, grid, 0, 0)) {
        sudokuGenerator(n, grid, k);
        return;
    }

    removeKDigits(n, grid, k);
}

void printBoard(int n, int grid[MAX_SIZE][MAX_SIZE]) {
    int square = (int)sqrt(n);
    int emptyCount = 0;
    fflush(stdout);

    printf("\n");
    for (int i = 0; i < n; i++) {
        // Print horizontal divider between boxes
        if (i % square == 0 && i != 0) {
            for (int j = 0; j < n; j++) {
                printf("---");
                if (j % square == square - 1 && j != n - 1) {
                    printf("-");
                }
            }
            printf("\n");
        }

        for (int j = 0; j < n; j++) {
            // Print vertical divider between boxes
            if (j % square == 0 && j != 0) {
                printf("| ");
            }

            if (grid[i][j] == 0) {
                printf(" . ");
                emptyCount++;
            } else {
                // Adjust spacing based on grid size
                if (n <= 9) {
                    printf("%2d ", grid[i][j]);
                } else {
                    // For 16x16, we need 2 digits
                    printf("%2d ", grid[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("\nEmpty cells: %d\n", emptyCount);
    fflush(stdout);
}

bool isBoardComplete(int n, int grid[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool isSolutionCorrect(int n, int grid[MAX_SIZE][MAX_SIZE]) {
    if (!isBoardComplete(n, grid)) {
        return false;
    }

    // Check rows and columns
    for (int i = 0; i < n; i++) {
        bool *rowCheck = calloc(n+1, sizeof(bool));
        bool *colCheck = calloc(n+1, sizeof(bool));

        if (!rowCheck || !colCheck) {
            if (rowCheck) free(rowCheck);
            if (colCheck) free(colCheck);
            return false;
        }

        for (int j = 0; j < n; j++) {
            // Check row
            int rowVal = grid[i][j];
            if (rowVal < 1 || rowVal > n || rowCheck[rowVal]) {
                free(rowCheck);
                free(colCheck);
                return false;
            }
            rowCheck[rowVal] = true;

            // Check column
            int colVal = grid[j][i];
            if (colVal < 1 || colVal > n || colCheck[colVal]) {
                free(rowCheck);
                free(colCheck);
                return false;
            }
            colCheck[colVal] = true;
        }

        free(rowCheck);
        free(colCheck);
    }

    // Check boxes
    int square = (int)sqrt(n);
    for (int boxRow = 0; boxRow < n; boxRow += square) {
        for (int boxCol = 0; boxCol < n; boxCol += square) {
            bool *boxCheck = calloc(n+1, sizeof(bool));
            if (!boxCheck) {
                return false;
            }

            for (int i = 0; i < square; i++) {
                for (int j = 0; j < square; j++) {
                    int val = grid[boxRow + i][boxCol + j];
                    if (val < 1 || val > n || boxCheck[val]) {
                        free(boxCheck);
                        return false;
                    }
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