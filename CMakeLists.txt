cmake_minimum_required(VERSION 3.30)
project(sudoku C)

set(CMAKE_C_STANDARD 11)

add_executable(sudoku main.c
        sudoku.h
        sasolver.c
        GA/GA.c
        GA/GAconfig.h
        GA/selections.h
        GA/selections.c
        GA/crossovers.c
        GA/crossovers.h
        GA/mutations.c
        GA/mutations.h
        GA/GAinterface.c
        sudokuMenu.c)
