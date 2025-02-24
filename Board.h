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
	bool solve(int row, int col);
	bool isEmptyCharacter(char c);

public:
	Board(std::string input);
	bool solve();
	void print();
	int valueAt(int row, int col);

};

