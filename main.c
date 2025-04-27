#include <math.h>
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

        switch (difficultyChoice) {
            case 1: return 4;
            case 2: return 9;
            case 3: return 16;
            case 4: return 0; // Back to main menu
            default:
                printf("Invalid choice. Please select 1-4.\n");
        }
    } while (true);
}
void printInstructions()
{
    printf("\n=== SUDOKU INSTRUCTIONS ===\n");
    printf("1. Start new game\n");
    printf("2. Choose board size\n");
    printf("3. Choose difficulty\n");
    printf("4. Fill the grid so that every row, column and box\n");
    printf("   contains all digits from 1 to N (where N is grid size)\n");
    printf("5. To make a move, enter row, column and value\n");
    printf("6. To remove a value, enter 0 as value\n");
    printf("7. Some cells are pre-filled (hints) - you can't change them\n\n");
    //TODO
    // Napisać jakieś podstawowe instrukcje jak obsugiwać grę

}
void startNewGame()
{
    int boardSize = selectBoardSize();
    int difficulty = selectDifficulty();
    //TODO
    // Zrobić mechanizm inicjalizacji planszy do sudoku o podanym wymiarze
    // potem następną fukncją wypełnić planszę liczbami zgodnie z rozmiarem i wybranym poziomem trudności

    //Number of cells to remove
    int k;
    switch (difficulty) {
        case 1: k = boardSize * boardSize / 2; break;    // Easy
        case 2: k = boardSize * boardSize * 2 / 3; break; // Medium
        case 3: k = boardSize * boardSize * 3 / 4; break; // Hard
        default: k = boardSize * boardSize / 2;
    }

    printf("\nStarting new game.\n");

    int grid[boardSize][boardSize];

    //todo
    // chyba trzena funkcje wcześniej zainicjować bo jak są stworzone później to ich nie widzi

    //sudokuGenerator();
    //printBoard();
}
void saveGame()
{
    printf("\nGame saved successfully!\n");
    //TODO
    // pomyśleć w jaki sposób zapisywać progress aktualnej rozgrywki do pliku
    // dodać też możlowść save'a do menu rozgrywki??

}
void loadGame()
{
    printf("\nGame loaded successfully!\n");
    //TODO
    // tu trzeba zrobić wyświetlanie dostępnych plików z savem w katalogu gry i możliwośc wyboru save'a
    //
}

//TODO
// pomyśleć jak obsługiwać ruchy gracza

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


// Returns false if given sqrt(n) x sqrt(n) block contains num
bool isSafeInBox(int n, int grid[n][n], int rowStart, int colStart, int num) {
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

// Fill a sqrt(n) x sqrt(n) matrix
void fillBox(int n, int grid[n][n], int row, int col) {
    int square = (int)sqrt(n);

    for (int i = 0; i < square; i++) {
        for (int j = 0; j < square; j++) {
            int num;
            do {
                num = (rand() % n) + 1;
            } while (!isSafeInBox(n, grid, row, col, num));
            grid[row + i][col + j] = num;
        }
    }
}


// Check if it's safe to put num in row i
bool isSafeInRow(int n, int grid[n][n], int i, int num) {
    for (int j = 0; j < n; j++) {
        if (grid[i][j] == num) {
            return false;
        }
    }
    return true;
}


// Check if it's safe to put num in column j
bool isSafeInCol(int n, int grid[n][n], int j, int num) {
    for (int i = 0; i < n; i++) {
        if (grid[i][j] == num) {
            return false;
        }
    }
    return true;
}


// Check if it's safe to put num in the cell (i, j)
bool checkIfSafe(int n, int grid[n][n], int i, int j, int num) {
    int square = (int)sqrt(n);
    return (isSafeInRow(n, grid, i, num) &&
           (isSafeInCol(n, grid, j, num) &&
           isSafeInBox(n, grid, i - i % square, j - j % square, num)));
}

// Fill the diagonal sqrt(n) x sqrt(n) matrices
void fillDiagonal(int n, int grid[n][n]) {
    int square = (int)sqrt(n);

    for (int i = 0; i < n; i += square) {
        fillBox(n, grid, i, i);
    }
}

// Fill remaining blocks in the grid
bool fillRemaining(int n, int grid[n][n], int i, int j) {
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

// Remove K digits randomly from the grid
void removeKDigits(int n, int grid [n][n], int k) {
    while (k > 0) {
        int cellId = rand() % (n*n);
        int i = cellId / n;
        int j = cellId % n;

        if (grid[i][j] != 0) {
            grid[i][j] = 0;
            k--;
        }
    }
}


// Generate a Sudoku grid with K empty cells
void sudokuGenerator(int n, int grid[n][n], int k) {
    // Initialize grid with 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = 0;
        }
    }

    fillDiagonal(n, grid);
    fillRemaining(n, grid, 0, 0);
    removeKDigits(n, grid, k);
}
void printBoard(int n, int grid[n][n]) {
    int square = (int)sqrt(n);
    for (int i = 0; i < n; i++) {
        if (i % square == 0 && i != 0) {
            for (int j = 0; j < n + square - 1; j++) {
                printf("---");
            }
            printf("\n");
        }

        for (int j = 0; j < n; j++) {
            if (j % square == 0 && j != 0) {
                printf("| ");
            }

            if (grid[i][j] == 0) {
                printf(" . ");
            } else {
                printf("%2d ", grid[i][j]);
            }
        }
        printf("\n");
    }
}


int main(void)
{
    //poziomy trurdności to ilość wygenerowanych liczb na nowej planszy(podpowiedzi)

    // zrobić menu główne i poboczne (do gry) z którego będzie można wykonywać ruchy i przejść do menu głównego
    // jak obliczać liczbę podpowiedzi względem rozmiaru planszy i poziomu trudddności?
    // zakres liczb zależy od wielkości planszy
    srand(time(0));

    printMainMenu();

    // int k = 30;
    // int sudoku[9][9];

    //sudokuGenerator(4, sudoku, k);


    // // Print the generated Sudoku puzzle
    // for (int i = 0; i < 9; i++) {
    //     for (int j = 0; j < 9; j++) {
    //         if (i%3 == 0 && j%3 == 0) {}
    //         printf("%d ", sudoku[i][j]);
    //     }
    //     printf("\n");
    // }
    return 0;
}
