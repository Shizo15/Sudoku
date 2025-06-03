#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "sudoku.h"

// Calculating energy (cost) - number of conflicts in rows and columns
static int calculateEnergy(int n, int grid[MAX_SIZE][MAX_SIZE]) {
    int conflicts = 0;

    // Checking rows
    for (int i = 0; i < n; i++) {
        int count[MAX_SIZE + 1] = {0};
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != 0) {
                count[grid[i][j]]++;
            }
        }
        for (int k = 1; k <= n; k++) {
            if (count[k] > 1) {
                conflicts += count[k] - 1;
            }
        }
    }

    // Checking columns
    for (int j = 0; j < n; j++) {
        int count[MAX_SIZE + 1] = {0};
        for (int i = 0; i < n; i++) {
            if (grid[i][j] != 0) {
                count[grid[i][j]]++;
            }
        }
        for (int k = 1; k <= n; k++) {
            if (count[k] > 1) {
                conflicts += count[k] - 1;
            }
        }
    }

    return conflicts;
}

// Generating neighbor state by swapping two cells in random block
static void generateNeighbor(int n, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]) {
    int square = (int)sqrt(n);

    // Choosing random block
    int blockRow = rand() % square;
    int blockCol = rand() % square;

    // Looking for all "empty" cells in this block
    int cells[MAX_SIZE * MAX_SIZE][2];
    int count = 0;

    for (int i = blockRow * square; i < (blockRow + 1) * square; i++) {
        for (int j = blockCol * square; j < (blockCol + 1) * square; j++) {
            if (initialGrid[i][j] == 0) {
                cells[count][0] = i;
                cells[count][1] = j;
                count++;
            }
        }
    }

    if (count < 2) return;

    // Choosing two different cells
    int idx1 = rand() % count;
    int idx2;
    do {
        idx2 = rand() % count;
    } while (idx2 == idx1);

    // Changing value of cells
    int temp = grid[cells[idx1][0]][cells[idx1][1]];
    grid[cells[idx1][0]][cells[idx1][1]] = grid[cells[idx2][0]][cells[idx2][1]];
    grid[cells[idx2][0]][cells[idx2][1]] = temp;
}

// Solver info header
static void printSolverHeader(int n) {
    printf("\n=== Starting solving with Simulated Annealing ===\n");
    printf("Parameters:\n");
    printf("- Board size: %dx%d\n", n, n);
    printf("- Start temperature: %.2f\n", 10.0);
    printf("- Cooling rate: %.3f\n", 0.99);
    printf("- Minimal temperature %.3f\n", 0.01);
    printf("- Max number of iterations: %d\n", 100000);
    printf("\n");
}

// Solver main func
void solveWithSA(int n, int grid[MAX_SIZE][MAX_SIZE], int initialGrid[MAX_SIZE][MAX_SIZE]) {
    printSolverHeader(n);

    int currentGrid[MAX_SIZE][MAX_SIZE];
    memcpy(currentGrid, grid, sizeof(int) * MAX_SIZE * MAX_SIZE);

    // Board initialization
    int square = (int)sqrt(n);
    for (int blockRow = 0; blockRow < square; blockRow++) {
        for (int blockCol = 0; blockCol < square; blockCol++) {
            bool used[MAX_SIZE + 1] = {false};
            for (int i = blockRow * square; i < (blockRow + 1) * square; i++) {
                for (int j = blockCol * square; j < (blockCol + 1) * square; j++) {
                    if (initialGrid[i][j] != 0) {
                        used[initialGrid[i][j]] = true;
                    }
                }
            }

            int num = 1;
            for (int i = blockRow * square; i < (blockRow + 1) * square; i++) {
                for (int j = blockCol * square; j < (blockCol + 1) * square; j++) {
                    if (initialGrid[i][j] == 0 && currentGrid[i][j] == 0) {
                        while (num <= n && used[num]) num++;
                        if (num <= n) {
                            currentGrid[i][j] = num;
                            used[num] = true;
                        } else {
                            currentGrid[i][j] = rand() % n + 1;
                        }
                    }
                }
            }
        }
    }

    // SA params - good to solve easy and medium 9x9 boards right now, and sometimes hard ones
    double temperature = 200.0;
    double coolingRate = 0.999;
    double minTemperature = 0.001;
    int maxIterations = 100000;
    int iterations = 0;

    int currentEnergy = calculateEnergy(n, currentGrid);
    int bestEnergy = currentEnergy;
    int bestGrid[MAX_SIZE][MAX_SIZE];
    memcpy(bestGrid, currentGrid, sizeof(int) * MAX_SIZE * MAX_SIZE);

    srand(time(NULL));


    printf("\n%10s %12s %12s %12s %12s\n",
           "Iterations", "Temperature", "Energy", "Best", "Acceptation");
    printf("%10s %12s %12s %12s %12s\n",
           "--------", "-----------", "-------", "---------", "----------");

    while (temperature > minTemperature && iterations < maxIterations && bestEnergy > 0) {
        int neighborGrid[MAX_SIZE][MAX_SIZE];
        memcpy(neighborGrid, currentGrid, sizeof(int) * MAX_SIZE * MAX_SIZE);
        generateNeighbor(n, neighborGrid, initialGrid);

        int neighborEnergy = calculateEnergy(n, neighborGrid);
        int deltaE = neighborEnergy - currentEnergy;

        int accepted = 0;
        double acceptanceProb = 0;

        if (deltaE < 0) {
            accepted = 1;
            acceptanceProb = 1.0;
        } else if (temperature > 0) {
            acceptanceProb = exp(-deltaE / temperature);
            if ((double)rand() / RAND_MAX < acceptanceProb) {
                accepted = 1;
            }
        }

        if (accepted) {
            memcpy(currentGrid, neighborGrid, sizeof(int) * MAX_SIZE * MAX_SIZE);
            currentEnergy = neighborEnergy;

            if (currentEnergy < bestEnergy) {
                bestEnergy = currentEnergy;
                memcpy(bestGrid, currentGrid, sizeof(int) * MAX_SIZE * MAX_SIZE);

                // Print info with parameters if better solution found
                printf("%10d %12.2f %12d %12d %12.2f%% *\n",
                       iterations, temperature, currentEnergy, bestEnergy,
                       acceptanceProb*100);
            }
        }

        //// Print every iteration
        printf("%10d %12.4f %12d %12d %12.2f%%\n",
                   iterations, temperature, currentEnergy, bestEnergy,
                   accepted ? acceptanceProb*100 : 0.0);

        temperature *= coolingRate;
        iterations++;
    }


    printf("\n=== Summary of results ===\n");
    printf("Ended after %d iterations\n", iterations);
    printf("Final temperature: %.4f\n", temperature);
    printf("Best number of conflicts: %d\n", bestEnergy);

    if (bestEnergy == 0) {
        printf("\nCorrect solution found!\n");

        printf("\nBest board found (conflicts: %d):\n", bestEnergy);
        printBoard(n, bestGrid);
        printf("\n");
    } else {
        printf("\nNo perfect solution has been found, here is the best: (%d conflicts):\n", bestEnergy);
        printBoard(n, bestGrid);
    }

    // Use the best solution found
    memcpy(grid, bestGrid, sizeof(int) * MAX_SIZE * MAX_SIZE);

    printf("\nPress Enter to continue...");
    fflush(stdout);
    clearInputBuffer();
    getchar();
}