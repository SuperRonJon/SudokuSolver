#pragma once
#include "Box.h"
#include <string>

class Board
{
	const int static BOARD_SIZE = 9;
	Box grid[BOARD_SIZE][BOARD_SIZE];

	bool isPossibility(int number, int row, int col);
	bool rowContains(int number, int row);
	bool columnContains(int number, int col);
	bool squareContains(int number, int row, int col);
	bool solve(int row, int col, long long& counter);
	bool isEmptyCharacter(char c);
	void printLine();

public:
	Board(std::string input);
	bool solve(long long& counter);
	void print(bool borders = false);
	int valueAt(int row, int col);

};

