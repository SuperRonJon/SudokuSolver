// SudokuSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include <string>
#include "InputParser.h"

void solveBoard(std::string boardString, bool borders);

int main(int argc, char* argv[])
{
    InputParser parser(argc, argv);
    
    bool bordersOn = parser.getBordersOn();
    std::string boardString = parser.getBoardString();
    if (boardString != "") {
        solveBoard(boardString, bordersOn);
        return 0;
    }
    return -1;
    
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


