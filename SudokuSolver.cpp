// SudokuSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include <string>
#include "InputParser.h"

void solveBoard(std::string boardString, bool borders);

int main(int argc, char* argv[])
{
    std::string exampleBoard = "x56xxx27872xx361xx8xxxxx46x5xxx47xxx4x9xxx7x5xxx65xxx4x35xxxxx7xx718xx32918xxx54x";
    InputParser parser(argc, argv);
    
    bool bordersOn = parser.getBordersOn();
    std::string boardString = parser.getBoardString();
    if (boardString == "example") {
        std::cout << "Example: " << exampleBoard << std::endl;
        return 0;
    }
    if (boardString != "") {
        solveBoard(boardString, bordersOn);
        return 0;
    }
    std::cout << "No board string detected. Must be 81 character string with one of x,X,0,o,O,. as empty characers." << std::endl;
    std::cout << "Example: " << exampleBoard << std::endl;
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


