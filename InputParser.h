#pragma once
#include <vector>
#include <string>

class InputParser
{
	std::vector<std::string> tokens;
	bool printBorders;
	std::string boardString;
	bool printBeforeSolved;
	bool fileInput;
	bool countChecks;

	std::vector<char> split(std::string options);
	void settingsFromTokens();
	bool startsWith(std::string token, char starting);
	void printTokens();
	void printOptions(std::vector<char> options);

	
public:
	InputParser(int argc, char* argv[]);
	bool getBordersOn();
	std::string getBoardString();
	bool getPrintBeforeSolved();
	bool isFileInput();
	bool getCountChecks();
};

