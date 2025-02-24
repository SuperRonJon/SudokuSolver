// SudokuSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include <string>

void solveBoard(std::string boardString, bool borders);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Invalid arguments. Enter single string representing sudoku board\n" <<
            "For example: x56xxx27872xx361xx8xxxxx46x5xxx47xxx4x9xxx7x5xxx65xxx4x35xxxxx7xx718xx32918xxx54x" << std::endl;
        return -1;
    }
    std::string boardString = argv[1];
    solveBoard(boardString, true);
}

void solveBoard(std::string boardString, bool borders) {
    if (boardString.size() != 81) {
        std::cout << "Invalid board string, incorrect length, must be 81 characters" << std::endl;
        return;
    }

    Board board(boardString);
    board.print(borders);
    if (board.solve()) {
        std::cout << "Solved!" << std::endl;
        board.print(borders);
    }
    else {
        std::cout << "Unable to solve..." << std::endl;
    }
}


