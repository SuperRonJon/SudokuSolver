#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Board.h"
#include "ArgumentParser.h"

#define VERSION "1.2"

long long solveBoard(const std::string &boardString, ArgumentParser &parser);
void solveBoardsFromFile(const std::string &fileName, ArgumentParser &parser);

ArgumentParser getParser();

int main(int argc, char* argv[])
{
    const std::string exampleBoard = "x56xxx27872xx361xx8xxxxx46x5xxx47xxx4x9xxx7x5xxx65xxx4x35xxxxx7xx718xx32918xxx54x";
    ArgumentParser parser = getParser();
    try {
        parser.parse(argc, argv);
    } catch(const std::invalid_argument &e) {
        std::cerr << "Argument error: " << e.what() << "\n";
        return 1;
    }

    if(parser.was_given("version")) {
        std::cout << "sudoku " << VERSION << "\n";
        return 0;
    }
    if(parser.was_given("help")) {
        parser.print_help();
        return 0;
    }
    if(parser.was_given("example")) {
        std::cout << "Example: " << exampleBoard << "\n";
        return 0;
    }
    
    std::string boardString;
    try {
        boardString = parser.get_unflagged_argument(0);
    } catch(const std::out_of_range &err) {
        boardString = "";
    }
    if (boardString == "example") {
        std::cout << "Example: " << exampleBoard << "\n";
        return 0;
    }
    if (boardString != "") {
        if (!parser.was_given("file")) {
            solveBoard(boardString, parser);
            return 0;
        }
        solveBoardsFromFile(boardString, parser);
        return 0;
    }
    
    std::string boardInput;
    bool hasTried = false;
    while (boardInput != "exit") {
        if (hasTried) {
            std::cout << "Invalid board... Try entering a board again.\n";
        }
        else {
            hasTried = true;
        }

        std::cout << "Enter board string here (or type exit to exit): ";
        std::cin >> boardInput;
        if (boardInput != "exit" && boardInput.size() == 81) {
            solveBoard(boardInput, parser);
            hasTried = false;
        }
        else if (boardInput == "example") {
            std::cout << "Example: " << exampleBoard << "\n";
            hasTried = false;
        }
    }

    return 0;
}

long long solveBoard(const std::string &boardString, ArgumentParser &parser) {
    const bool borders = parser.was_given("borders");
    const bool printBeforeSolved = !parser.was_given("print-solved");
    const bool countChecks = parser.was_given("count");
    if (boardString.size() != 81) {
        std::cout << "Invalid board string, incorrect length, must be 81 characters\n";
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
            std::cout << "Solved in " << counter << " checks!\n";
        else
            std::cout << "Solved!\n";
        board.print(borders);
    }
    else {
        if (counter != -1)
            std::cout << "Unable to solve after " << counter << " checks...\n";
        else
            std::cout << "Unable to solve...\n";
    }
    return counter;
}

void solveBoardsFromFile(const std::string &fileName, ArgumentParser &parser) {
    std::ifstream infile(fileName);
    std::string line;
    std::vector<std::string> bigCounts;
    int min_counts;
    try {
        min_counts = std::stoi(parser.get_value("required-checks"));
    } catch(const std::exception &err) {
        std::cerr << "Error parsing required checks value " << parser.get_value("required-checks") << " to integer.\n";
        return;
    }
    
    int count = 0;
    while (infile >> line) {
        count++;
        std::cout << "Puzzle #" << count << " - " << line << "\n";
        long long count = solveBoard(line, parser);
        if (count >= min_counts && min_counts != -1) {
            bigCounts.push_back(line);
        }
    }

    if (min_counts != -1) {
        std::cout << "Puzzles with required checks over " << min_counts << "\n";
        std::cout << "==========================================\n";
        for (std::size_t i = 0; i < bigCounts.size(); i++) {
            std::cout << bigCounts[i] << "\n";
        }
    }
    
}

ArgumentParser getParser() {
    ArgumentParser parser("Sudoku Solver", "sudoku [OPTIONS...] <board-string>|<file-path>");
    parser.add_option('b', "borders", "Print board with border lines.");
    parser.add_option('p', "print-solved", "Prints only the solved board, not the starting board.");
    parser.add_option('f', "file", "Reads boards line by line from an input file path rather than a single string.");
    parser.add_option('c', "count", "Prints the total number of individual box checks required to solve.");
    parser.add_option('r', "required-checks", true, "-1", "If counting and from a file input, prints all boards in file above this number of checks.");
    parser.add_option('e', "example", "Prints an example valid board string.");
    parser.add_option('v', "version", "Prints version number.");
    parser.add_option('h', "help", "Prints help menu.");
    return parser;
}
