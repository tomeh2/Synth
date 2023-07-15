#pragma once

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
public:
	void tokenizeFile(FILE* file, std::vector<std::string>* tokens);
};

