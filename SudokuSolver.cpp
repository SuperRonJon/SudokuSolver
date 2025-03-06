// SudokuSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Board.h"
#include "InputParser.h"

long long solveBoard(std::string boardString, InputParser parser);
void solveBoardsFromFile(std::string fileName, InputParser parser);

int main(int argc, char* argv[])
{
    std::string exampleBoard = "x56xxx27872xx361xx8xxxxx46x5xxx47xxx4x9xxx7x5xxx65xxx4x35xxxxx7xx718xx32918xxx54x";
    InputParser parser(argc, argv);
    
    std::string boardString = parser.getBoardString();
    if (boardString == "example") {
        std::cout << "Example: " << exampleBoard << std::endl;
        return 0;
    }
    if (boardString != "") {
        if (!parser.isFileInput()) {
            solveBoard(boardString, parser);
            return 0;
        }
        solveBoardsFromFile(boardString, parser);
        return 0;
    }
    
    std::string boardInput = "";
    bool hasTried = false;
    do {
        if (hasTried) {
            std::cout << "Invalid board... Try entering a board again." << std::endl;
        }
        else {
            hasTried = true;
        }

        std::cout << "Enter board string here (or type exit to exit): ";
        std::cin >> boardInput;
        std::cout << std::endl;
        if (boardInput != "exit" && boardInput.size() == 81) {
            solveBoard(boardInput, parser);
            hasTried = false;
        }
    } while (boardInput != "exit");

    return 0;
}

long long solveBoard(std::string boardString, InputParser parser) {
    bool borders = parser.getBordersOn();
    bool printBeforeSolved = parser.getPrintBeforeSolved();
    bool countChecks = parser.getCountChecks();
    if (boardString.size() != 81) {
        std::cout << "Invalid board string, incorrect length, must be 81 characters" << std::endl;
        return -1;
    }

    Board board(boardString);
    if(printBeforeSolved)
        board.print(borders);
    long long counter = -1;
    if (countChecks)
        counter = 0;
        
    if (board.solve(counter)) {
        if (counter != -1)
            std::cout << "Solved in " << counter << " checks!" << std::endl;
        else
            std::cout << "Solved!" << std::endl;
        board.print(borders);
    }
    else {
        if (counter != -1)
            std::cout << "Unable to solve after " << counter << " checks..." << std::endl;
        else
            std::cout << "Unable to solve..." << std::endl;
    }
    return counter;
}

void solveBoardsFromFile(std::string fileName, InputParser parser) {
    std::ifstream infile(fileName);
    std::string line;
    std::vector<std::string> bigCounts;
    const int MIN_COUNTS = parser.getMinChecks();
    int count = 0;
    while (infile >> line) {
        count++;
        std::cout << "Puzzle #" << count << " - " << line << std::endl;
        long long count = solveBoard(line, parser);
        if (count >= MIN_COUNTS && MIN_COUNTS != -1) {
            bigCounts.push_back(line);
        }
    }

    if (MIN_COUNTS != -1) {
        std::cout << "Puzzles with required checks over " << MIN_COUNTS << std::endl;
        std::cout << "==========================================" << std::endl;
        for (int i = 0; i < bigCounts.size(); i++) {
            std::cout << bigCounts[i] << std::endl;
        }
    }
    
}


