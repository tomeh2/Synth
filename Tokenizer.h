#pragma once

#include "Token.h"

#include <string>
#include <vector>
#include <fstream>

class Tokenizer
{
private:
	FILE* file;
	std::string str;

	char wsLow = 0;
	char wsHigh = 32;

	int strIndex = 0;

	int isEOF();
	int isEOS();
	void movePointer(int val);
	bool isWhitespace(char c);
	bool isSeparatorChar(char c);
	bool isNumeric(char c);
	bool isAlpha(char c);
	int getNextToken(Token* t);
	char getNextChar();
public:
	Tokenizer(FILE* file);
	Tokenizer(std::string str);

	void tokenize(std::vector<Token*>* tokens);
};

