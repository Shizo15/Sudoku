#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


void clearInputBuffer() {
    while (getchar() != '\n');
}

int selectBoardSize()
{
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
        case 1: return 4;
        case 2: return 9;
        case 3: return 16;
        case 4: return 0; // Back to main menu
        default:
            printf("Invalid choice. Please select 1-4.\n");
        }
    } while (true);
}

int selectDifficulty()
{
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

        if (difficultyChoice >= 1 && difficultyChoice <= 4) {
            return difficultyChoice;
        }
        printf("Invalid choice. Please select 1-4.\n");
    } while (true);
}
void printInstructions()
{
    printf("\nInstructions:\n");

}
void startNewGame()
{

}
void saveGame()
{
    printf("\nGame saved successfully!\n");

}
void loadGame()
{
    printf("\nGame loaded successfully!\n");

}

// inne funkcje

void printMainMenu()
{
    int choice;
    while (true) {
        printf("\n=== SUDOKU MENU ===\n");
        printf("1. New Game\n");
        printf("2. Instructions\n");
        printf("3. Save Game\n");
        printf("4. Load Game\n");
        printf("5. Exit\n");
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
        case 1: startNewGame(); break;
        case 2: printInstructions(); break;
        case 3: saveGame(); break;
        case 4: loadGame(); break;
        case 5:
            printf("\nGoodbye!\n");
            return;
        default:
            printf("Invalid choice. Please select 1-5.\n");
        }
    }
}

//PRZEPISANE SUDOKU ZE STRONY

// Returns false if given 3x3 block contains num
bool unUsedInBox(int grid[9][9], int rowStart, int colStart, int num) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[rowStart + i][colStart + j] == num) {
                return false;
            }
        }
    }
    return true;
}

// Fill a 3x3 matrix
void fillBox(int grid[9][9], int row, int col) {
    int num;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            do {
                num = (rand() % 9) + 1;
            } while (!unUsedInBox(grid, row, col, num));
            grid[row + i][col + j] = num;
        }
    }
}

// Check if it's safe to put num in row i
bool unUsedInRow(int grid[9][9], int i, int num) {
    for (int j = 0; j < 9; j++) {
        if (grid[i][j] == num) {
            return false;
        }
    }
    return true;
}

// Check if it's safe to put num in column j
bool unUsedInCol(int grid[9][9], int j, int num) {
    for (int i = 0; i < 9; i++) {
        if (grid[i][j] == num) {
            return false;
        }
    }
    return true;
}

// Check if it's safe to put num in the cell (i, j)
bool checkIfSafe(int grid[9][9], int i, int j, int num) {
    return (unUsedInRow(grid, i, num) &&
           (unUsedInCol(grid, j, num) &&
           unUsedInBox(grid, i - i % 3, j - j % 3, num)));
}

// Fill the diagonal 3x3 matrices
void fillDiagonal(int grid[9][9]) {
    for (int i = 0; i < 9; i += 3) {
        fillBox(grid, i, i);
    }
}

// Fill remaining blocks in the grid
bool fillRemaining(int grid[9][9], int i, int j) {
    if (i == 9) {
        return true;
    }

    if (j == 9) {
        return fillRemaining(grid, i + 1, 0);
    }

    if (grid[i][j] != 0) {
        return fillRemaining(grid, i, j + 1);
    }

    for (int num = 1; num <= 9; num++) {
        if (checkIfSafe(grid, i, j, num)) {
            grid[i][j] = num;
            if (fillRemaining(grid, i, j + 1)) {
                return true;
            }
            grid[i][j] = 0;
        }
    }

    return false;
}

// Remove K digits randomly from the grid
void removeKDigits(int grid[9][9], int k) {
    while (k > 0) {
        int cellId = rand() % 81;
        int i = cellId / 9;
        int j = cellId % 9;

        if (grid[i][j] != 0) {
            grid[i][j] = 0;
            k--;
        }
    }
}

// Generate a Sudoku grid with K empty cells
void sudokuGenerator(int grid[9][9], int k) {
    // Initialize grid with 0
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid[i][j] = 0;
        }
    }

    fillDiagonal(grid);
    fillRemaining(grid, 0, 0);
    removeKDigits(grid, k);
}


int main(void)
{
    //poziomy trurdności to ilość wygenerowanych liczb na nowej planszy(podpowiedzi)

    // zrobić menu główne i poboczne (do gry) z którego będzie można wykonywać ruchy i prześć do menu głównego
    // printMainMenu();


    //PRZEPISANE SUDOKU

    srand(time(0));
    int k = 20;
    int sudoku[9][9];

    sudokuGenerator(sudoku, k);

    // Print the generated Sudoku puzzle
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (i%3 == 0 && j%3 == 0) {}
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
    return 0;
}
