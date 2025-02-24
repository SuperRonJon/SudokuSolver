#include "Board.h"
#include <iostream>

Board::Board(std::string input) {
	int index = 0;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (!isEmptyCharacter(input[index])) {
				grid[i][j] = Box(input[index] - '0');
			}
			else {
				grid[i][j] = Box();
			}
			index++;
		}
	}
}
void Board::print(bool borders) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (borders && i != 0 && i % 3 == 0) {
			printLine();
		}
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (borders && j != 0 && j % 3 == 0) {
				std::cout << "| ";
			}
			if (!grid[i][j].isEmpty()) {
				std::cout << std::to_string(grid[i][j].getValue()) << " ";
			}
			else {
				std::cout << "x ";
			}
		}
		std::cout << std::endl;
	}
}

void Board::printLine() {
	std::cout << "---------------------" << std::endl;
}

bool Board::isPossibility(int number, int row, int col) {
	return (!rowContains(number, row) && !columnContains(number, col) && !squareContains(number, row, col));
}

bool Board::rowContains(int number, int row) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (grid[row][i].getValue() == number)
			return true;
	}
	return false;
}
bool Board::columnContains(int number, int col) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (grid[i][col].getValue() == number)
			return true;
	}
	return false;
}

bool Board::squareContains(int number, int row, int col) {
	int startRow = row - (row % 3);
	int startCol = col - (col % 3);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (grid[i + startRow][j + startCol].getValue() == number) {
				return true;
			}
		}
	}
	return false;
}

int Board::valueAt(int row, int col) {
	return grid[row][col].getValue();
}

bool Board::solve() {
	return solve(0, 0);
}

bool Board::solve(int row, int col) {
	if (row == BOARD_SIZE - 1 && col == BOARD_SIZE) 
		return true;
	if (col == BOARD_SIZE) {
		row++;
		col = 0;
	}

	if (!grid[row][col].isEmpty())
		return solve(row, col+1);

	for (int i = 1; i <= BOARD_SIZE; i++) {
		if (isPossibility(i, row, col)) {
			grid[row][col].setValue(i);
			if (solve(row, col + 1)) {
				return true;
			}
			grid[row][col].clear();
		}
	}
	return false;
}

bool Board::isEmptyCharacter(char c) {
	return (c == 'x' || c == 'X' || c == '0' || c == 'O' || c == 'o' || c == '.');
}