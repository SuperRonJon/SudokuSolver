#include "InputParser.h"
#include <iostream>

std::vector<char> InputParser::split(std::string options) {
	if (options.size() == 1) {
		std::vector<char> result;
		result.push_back(options[0]);
		return result;
	}
	std::vector<char> chars;
	for (int i = 0; i < options.size(); i++) {
		chars.push_back(options[i]);
	}
	return chars;
}

InputParser::InputParser(int argc, char* argv[]) {
	for (int i = 0; i < argc; i++) {
		tokens.push_back(argv[i]);
	}
	settingsFromTokens();
}

void InputParser::printTokens() {
	for (int i = 0; i < tokens.size(); i++) {
		std::cout << tokens[i] << std::endl;
	}
}

void InputParser::printOptions(std::vector<char> options) {
	for (int i = 0; i < options.size(); i++) {
		std::cout << options[i] << std::endl;
	}
}

void InputParser::settingsFromTokens() {
	if (tokens.size() < 2) {
		printBorders = false;
		boardString = "";
		return;
	}
	if (tokens.size() == 2 && !startsWith(tokens[1], '-')) {
		
		printBorders = false;
		boardString = tokens[1];
		return;
	}
	if (tokens.size() == 2 && startsWith(tokens[1], '-')) {
		printBorders = false;
		boardString = "";
		return;
	}
	for (int i = 0; i < tokens.size(); i++) {
		if (startsWith(tokens[i], '-')) {
			std::string options = tokens[i].substr(1, tokens[i].size() - 1);
			std::vector<char> splitOptions = split(options);
			for (int j = 0; j < splitOptions.size(); j++) {
				switch (splitOptions[j]) {
				case 'b':
					printBorders = true;
				}
			}
		}
	}
	boardString = tokens[tokens.size() - 1];
}

bool InputParser::startsWith(std::string token, char starting) {
	if (token[0] == starting) return true;
	return false;
}

bool InputParser::getBordersOn() {
	return printBorders;
}

std::string InputParser::getBoardString() {
	return boardString;
}

