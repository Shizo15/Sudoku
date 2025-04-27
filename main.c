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

        if (difficultyChoice >= 1 && difficultyChoice <= 4) {
            return difficultyChoice;
        }
        printf("Invalid choice. Please select 1-4.\n");
    } while (true);
}
void printInstructions()
{
    printf("\nInstructions:\n");
    //TODO
    // Napisać jakieś podstawowe instrukcje jak obsugiwać grę

}
void startNewGame()
{
    selectBoardSize();
    selectDifficulty();
    //TODO
    // Zrobić mechanizm inicjalizacji planszy do sudoku o podanym wymiarze
    // potem następną fukncją wypełnić planszę liczbami zgodnie z rozmiarem i wybranym poziomem trudności

    printf("\nStarting new game.\n");

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

// inne funkcje
//TODO
// zroibć logikę gry i pomyśleć jak obsługiwać ruchy gracza

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
bool isSafeInBox(int grid[9][9], int rowStart, int colStart, int num) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[rowStart + i][colStart + j] == num) {
                return false;
            }
        }
    }
    return true;
}
//todo
// tutaj przerobić na generowanie wartości zależnie od wybranej wielkości

// Fill a 3x3 matrix
void fillBox(int grid[9][9], int row, int col) {
    int num;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            do {
                num = (rand() % 9) + 1;
            } while (!isSafeInBox(grid, row, col, num));
            grid[row + i][col + j] = num;
        }
    }
}
//todo
// tutaj przerobić na sprawdzanie wartości zależnie od wybranej wielkości

// Check if it's safe to put num in row i
bool isSafeInRow(int grid[9][9], int i, int num) {
    for (int j = 0; j < 9; j++) {
        if (grid[i][j] == num) {
            return false;
        }
    }
    return true;
}
//todo
// tutaj przerobić na sprawdzanie wartości zależnie od wybranej wielkości

// Check if it's safe to put num in column j
bool isSafeInCol(int grid[9][9], int j, int num) {
    for (int i = 0; i < 9; i++) {
        if (grid[i][j] == num) {
            return false;
        }
    }
    return true;
}
//todo
// tutaj przerobić na sprawdzanie wartości zależnie od wybranej wielkości

// Check if it's safe to put num in the cell (i, j)
bool checkIfSafe(int n, int i, int j, int num) {
    int square = (int)sqrt(n);
    int grid[n][n];
    return (isSafeInRow(grid, i, num) &&
           (isSafeInCol(grid, j, num) &&
           isSafeInBox(grid, i - i % square, j - j % square, num)));
}
//todo
// tutaj przerobić na generowanie wartości zależnie od wybranej wielkości

// Fill the diagonal 3x3 matrices
void fillDiagonal(int n) {
    int grid[n][n];
    int square = (int)sqrt(n);

    for (int i = 0; i < n; i += square) {
        fillBox(grid, i, i);
    }
}
//todo
// tutaj przerobić na generowanie wartości zależnie od wybranej wielkości

// Fill remaining blocks in the grid
bool fillRemaining(int n, int i, int j) {
    int grid[n][n];
    if (i == n) {
        return true;
    }

    if (j == 9) {
        return fillRemaining(grid, i + 1, 0);
    }

    if (grid[i][j] != 0) {
        return fillRemaining(grid, i, j + 1);
    }

    for (int num = 1; num <= n; num++) {
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
//todo
// tutaj przerobić na generowanie wartości zależnie od wybranej wielkości
// dodać usuwanie pól zaleźnie od poziomu trudności

// Remove K digits randomly from the grid
void removeKDigits(int n, int k) {
    int grid [n][n];
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
//todo
// tutaj przerobić na generowanie wartości zależnie od wybranej wielkości

// Generate a Sudoku grid with K empty cells
void sudokuGenerator(int n, int k) {
    // Initialize grid with 0
    int grid[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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

    // zrobić menu główne i poboczne (do gry) z którego będzie można wykonywać ruchy i przejść do menu głównego
    // jak obliczać liczbę podpowiedzi względem rozmiaru planszy i poziomu trudddności?
    // zakres liczb zależy od wielkości planszy

    printMainMenu();


    //PRZEPISANE SUDOKU
    //todo
    // to trzeba przenieść do metody startującej gre
    srand(time(0));
    int k = 30;
    int sudoku[9][9];

    sudokuGenerator(sudoku, k);
    //
    //todo
    // to trzeba będzie prtinować i aktualizować w każdej iteracji gry / po każdej akcji

    // Print the generated Sudoku puzzle
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (i%3 == 0 && j%3 == 0) {}
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
    //todo
    // dodać memiki oczywiście do readme
    return 0;
}
