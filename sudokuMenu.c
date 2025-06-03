#include <stdio.h>
#include <stdbool.h>
#include "sudoku.h"
#include <stdlib.h>


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

//Draws main menu and responds to user sekection
void printMainMenu() {
    int choice;
    do {
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
        case 2:
            {
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
    printf("4. Solve with Simulated Annealing\n");
    printf("5. Solve with Genetic Algorithm\n");
    printf("6. Back to main menu\n");
}