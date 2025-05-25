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
	printBorders = false;
	printBeforeSolved = true;
	fileInput = false;
	countChecks = false;
	minChecks = -1;
	printVersion = false;
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
	bool setBoardString = true;
	if (tokens.size() < 2) {
		boardString = "";
		return;
	}
	if (tokens.size() == 2 && !startsWith(tokens[1], '-')) {
		
		boardString = tokens[1];
		return;
	}
	if (tokens.size() == 2 && startsWith(tokens[1], '-')) {
		boardString = "";
		setBoardString = false;
	}
	int minChecksTokenIndex = -1;
	for (int i = 0; i < tokens.size(); i++) {
		if (startsWith(tokens[i], "--")) {
			std::string command = tokens[i].substr(2, tokens[i].size() - 1);
			if (command == "version") {
				printVersion = true;
			}
		}
		else if (startsWith(tokens[i], '-')) {
			std::string options = tokens[i].substr(1, tokens[i].size() - 1);
			for (int j = 0; j < options.size(); j++) {
				switch (options[j]) {
				case 'b':
					printBorders = true;
					break;
				case 'p':
					printBeforeSolved = false;
					break;
				case 'f':
					fileInput = true;
					break;
				case 'c':
					countChecks = true;
					break;
				case 'r':
					minChecksTokenIndex = i+1;
					break;
				}
			}
		}
		else {
			if (i == minChecksTokenIndex && i != tokens.size() - 1) {
				minChecks = std::stoi(tokens[i]);
			}
		}
	}
	if(setBoardString)
		boardString = tokens[tokens.size() - 1];
}

bool InputParser::startsWith(std::string token, char starting) {
	if (token[0] == starting) return true;
	return false;
}

bool InputParser::startsWith(std::string token, std::string starting) {
	if(token.rfind(starting, 0) == 0) return true;
	return false;
}

bool InputParser::getBordersOn() {
	return printBorders;
}

std::string InputParser::getBoardString() {
	return boardString;
}

bool InputParser::getPrintBeforeSolved() {
	return printBeforeSolved;
}

bool InputParser::isFileInput() {
	return fileInput;
}

bool InputParser::getCountChecks() {
	return countChecks;
}

int InputParser::getMinChecks() {
	return minChecks;
}

bool InputParser::getPrintVersion() {
	return printVersion;
}
