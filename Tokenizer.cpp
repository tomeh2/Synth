#include "Tokenizer.h"

bool Tokenizer::isWhitespace(char c)
{
	return c >= wsLow && c <= wsHigh ? true : false;
}

bool Tokenizer::isSeparatorChar(char c)
{
	return (c == '=' ||
		c == '{' ||
		c == '}' ||
		c == ';') ? true : false;
}

void Tokenizer::tokenizeFile(FILE* file, std::vector<std::string>* tokens)
{
	char readChar;

	std::string token;
	while (!feof(file))
	{
		readChar = fgetc(file);

		if (isWhitespace(readChar))
		{
			if (token.size() > 0)
				tokens->insert(tokens->end(), token);
			token.clear();
		}
		else if (isSeparatorChar(readChar))
		{
			if (token.size() > 0)
				tokens->insert(tokens->end(), token);
			token.clear();
			token.insert(token.end(), readChar);
			tokens->insert(tokens->end(), token);
			token.clear();
		}
		else
			token.insert(token.end(), readChar);
	}
}
