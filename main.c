#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

void clearInputBuffer();
int selectBoardSize();
int selectDifficulty();
void printInstructions();
void startNewGame();
void saveGame();
void loadGame();
void printMainMenu();
void printGameMenu();
void clearScreen();

bool isSafeInBox(int n, int grid[n][n], int rowStart, int colStart, int num);
void fillBox(int n, int grid[n][n], int row, int col);
bool isSafeInRow(int n, int grid[n][n], int i, int num);
bool isSafeInCol(int n, int grid[n][n], int j, int num);
bool checkIfSafe(int n, int grid[n][n], int i, int j, int num);
void fillDiagonal(int n, int grid[n][n]);
bool fillRemaining(int n, int grid[n][n], int i, int j);
void removeKDigits(int n, int grid[n][n], int k);
void sudokuGenerator(int n, int grid[n][n], int k);
void printBoard(int n, int grid[n][n]);
void gameLoop(int n, int grid[n][n], int initialGrid[n][n]);
bool makeMove(int n, int grid[n][n], int initialGrid[n][n]);
bool isHintCell(int n, int initialGrid[n][n], int row, int col);
bool isBoardComplete(int n, int grid[n][n]);
bool isSolutionCorrect(int n, int grid[n][n]);

void clearScreen()
{
    system("cls");
}

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
            case 4: return 0;
            default:
                printf("Invalid choice. Please select 1-4.\n");
        }
    } while (true);
}
void printInstructions()
{
    // printf("\n=== SUDOKU INSTRUCTIONS ===\n");
    // printf("1. Start new game\n");
    // printf("2. Choose board size\n");
    // printf("3. Choose difficulty\n");
    // printf("4. Fill the grid so that every row, column and box\n");
    // printf("   contains all digits from 1 to N (where N is grid size)\n");
    // printf("5. To make a move, enter row, column and value\n");
    // printf("6. To remove a value, enter 0 as value\n");
    // printf("7. Some cells are pre-filled (hints) - you can't change them\n\n");

    clearScreen();
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
void startNewGame()
{
    clearScreen();
    int boardSize = selectBoardSize();
    if (boardSize==0) return;

    clearScreen();
    int difficulty = selectDifficulty();
    if (difficulty==4) return;

    clearInputBuffer();

    //Number of cells to remove
    int k;
    switch (difficulty) {
        case 1:
            k = boardSize * boardSize / 2; break;    // Easy
        case 2:
            k = boardSize * boardSize * 2 / 3; break; // Medium
        case 3:
            k = boardSize * boardSize * 3 / 4; break; // Hard
        default:
            k = boardSize * boardSize / 2;
    }

    int grid[boardSize][boardSize];
    int initialGrid[boardSize][boardSize]; //original hints

    sudokuGenerator(boardSize, grid, k);
    memcpy(initialGrid, grid,sizeof(initialGrid));

    clearScreen();
    printf("\n=== NEW GAME STARTED ===\n");
    printf("Size: %dx%d | Difficulty: %d\n\n", boardSize, boardSize, difficulty);
    printBoard(boardSize, grid);

    gameLoop(boardSize, grid, initialGrid);

}
bool isHintCell(int n, int initialGrid[n][n], int row, int col)
{
    return initialGrid[row][col] != 0;
}

bool makeMove(int n, int grid[n][n], int initialGrid[n][n])
{
    int row, col, num;

    printf("Enter row, column and value (1-%d) or 0 to clear: ",n);
    if (scanf("%d %d %d",&row, &col, &num) != 3)
    {
        clearInputBuffer();
        return false;
    }

    if(row < 1 || row > n || col < 1 || col > n) {
        return false;
    }

    if(num < 0 || num > n) {
        return false;
    }

    row--;
    col--;

    if (isHintCell(n, initialGrid, row, col)) {
        printf("Cannot modify hint cells!\n");
        return false;
    }

    grid[row][col] = num;
    return true;
}

void gameLoop(int n, int grid[n][n], int initialGrid[n][n])
{
    time_t startTime = time(NULL);
    int choice;
    bool gameRunning = true;

    while (gameRunning)
    {
        clearScreen();
        printf("\n=== SUDOKU GAME ===\n");
        printf("Size: %dx%d", n, n);
        printBoard(n, grid);

        if (isBoardComplete(n, grid))
        {
            if (isSolutionCorrect(n, grid))
            {
                printf("\nCongratulations! You solved Sudoku\n");
                time_t endTime = time(NULL);
                printf("Time: %.0f seconds\n", difftime(endTime, startTime));
                gameRunning = false;
                printf("\nPress Enter to continue...");
                clearInputBuffer();
                getchar();
                // continue;
            }
            else
            {
                printf("\nSome cells are incorrect. Keep trying.\n");
            }
        }

        printGameMenu();

        printf("Your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            clearInputBuffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        switch (choice)
        {
            case 1:
                if (!makeMove(n, grid, initialGrid))
                {
                    printf("Invalid move.\n");
                }
                break;
            case 2:
                saveGame(n, grid);
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

    }
    if (isSolutionCorrect(n, grid))
    {
        time_t endTime = time(NULL);
        printf("Time: %.0f seconds \n", difftime(endTime, startTime));
    }
}
void saveGame(int n, int grid[n][n])
{
    printf("\nGame saved successfully!\n");
    printf("Press Enter to continue...");
    clearInputBuffer();
    getchar();
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

void printMainMenu()
{
    int choice;
    while (true) {
        printf("\n=== SUDOKU MENU ===\n");
        printf("1. New Game\n");
        printf("2. Instructions\n");
        printf("3. Load Game\n");
        printf("4. Exit\n");
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
        case 1: startNewGame(); break;
        case 2: printInstructions(); break;
        case 3: loadGame(); break;
        case 4:
            printf("\nGoodbye!\n");
            return;
        default:
            printf("Invalid choice. Please select 1-4.\n");
        }
    }
}
void printGameMenu()
{
    printf("\n=== GAME MENU ===\n");
    printf("1. Make a move\n");
    printf("2. Save game\n");
    printf("3. Show instructions\n");
    printf("4. Back to main menu\n");
    printf("Your choice: ");

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
    int emptyCount = 0;

    printf("\n");
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
                emptyCount++;
            }
            else {
                printf("%2d ", grid[i][j]);
            }
        }
        printf("\n");
    }
    printf("\nEmpty cells: %d", emptyCount);
}

bool isBoardComplete(int n, int grid[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}
bool isSolutionCorrect(int n, int grid[n][n])
{
    if (!isBoardComplete(n, grid))
    {
        return false;
    }

    for (int i = 1; i <=n; i++)
    {
        for (int j = 0; j<=n; j++)
        {
            bool foundInRow = false;
            bool foundInCol = false;
            for (int k = 0; k<n; k++)
            {
                if (grid[j][k] == i)
                {
                    foundInRow = true;
                }
                if (grid[k][j] == i)
                {
                    foundInCol = true;
                }
            }
            if (!foundInRow || !foundInCol)
            {
                return false;
            }
        }
        int square = (int)sqrt(n);
        for (int boxRow = 0; boxRow < n; boxRow+=square)
        {
            for (int boxCol = 0; boxCol < n; boxCol+=square)
            {
                bool foundInBox = false;
                for (int l = 0; l < square; l++)
                {
                    for (int m = 0; m < square; m++)
                    {
                        if (grid[boxRow + l][boxCol+m] == i)
                        {
                            foundInBox = true;
                        }
                    }
                }
                if (!foundInBox)
                {
                    return false;
                }
            }
        }
    }
    return true;
}


int main(void)
{

    srand(time(0));
    printMainMenu();

    //TODO
    // zrobić statystyki gry - czas rozgrywki, pomyłki
    // można dodać licznik ile zostało pustych miejsc
    // zrobić zapisywanie progressu do pliku
    // odczytywanie progressu z pliku

    return 0;
}
