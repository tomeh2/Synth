#pragma once

#include "Token.h"

#include <string>
#include <vector>
#include <fstream>

class Tokenizer
{
private:
	char wsLow = 0;
	char wsHigh = 32;

	int state = 0;
	bool isWhitespace(char c);
	bool isSeparatorChar(char c);
	bool isNumeric(char c);
	bool isAlpha(char c);
	int getNextToken(FILE* file, Token* t);
public:
	void tokenizeFile(FILE* file, std::vector<std::string>* tokens);
};

