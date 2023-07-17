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

bool Tokenizer::isNumeric(char c)
{
	return (c >= 48 && c <= 57) || c == 46 ? true : false;
}

bool Tokenizer::isAlpha(char c)
{
	return c >= 65 && c <= 90 || c >= 97 && c <= 122 ? true : false;
}



int Tokenizer::getNextToken(FILE* file, Token* t)
{
	bool done = false;

	char readChar;
	std::string tokenVal = "";
	bool first = true;
	while (!feof(file) && !done)
	{
		readChar = fgetc(file);

		if (first)
		{
			if (readChar == '{')
			{
				t->setType(Token::CURLY_START);
				return 0;
			}
			else if (readChar == '}')
			{
				t->setType(Token::CURLY_END);
				return 0;
			}
			else if (readChar == '=')
			{
				t->setType(Token::EQUALS);
				return 0;
			}
			else if (readChar == ';')
			{
				t->setType(Token::SEMICOLON);
				return 0;
			}
			else if (isNumeric(readChar))
				t->setType(Token::NUMBER_INT);
			else if (isAlpha(readChar))
				t->setType(Token::STRING);
			else
			{
				t->setType(Token::NULLTOKEN);
				return 0;
			}
			first = false;
		}

		if (t->getType() == Token::NUMBER_INT && readChar == '.')
		{
			t->setType(Token::NUMBER_FLOAT);
			tokenVal.insert(tokenVal.end(), readChar);
		}
		else if ((t->getType() == Token::NUMBER_INT || t->getType() == Token::NUMBER_FLOAT) && !isNumeric(readChar))
		{
			fseek(file, -1, SEEK_CUR);
			done = true;
		}
		else if (t->getType() == Token::STRING && !isAlpha(readChar) && !isNumeric(readChar))
		{
			fseek(file, -1, SEEK_CUR);
			done = true;
		}
		else
		{
			tokenVal.insert(tokenVal.end(), readChar);
		}
	}

	if (t->getType() == Token::NUMBER_INT)
		t->setIntData(atoi(tokenVal.c_str()));
	else if (t->getType() == Token::NUMBER_FLOAT)
		t->setFloatData(atof(tokenVal.c_str()));
	else if (t->getType() == Token::STRING)
		t->setStringData(tokenVal);

	if (feof(file))
		return -1;
	else
		return 0;
}

void Tokenizer::tokenizeFile(FILE* file, std::vector<std::string>* tokens)
{
	char readChar;

	std::string token;
	Token t(Token::NULLTOKEN);
	while (getNextToken(file, &t) != -1)
	{
		if (t.getType() == Token::NUMBER_INT)
			printf("Type: INT | Val: %d\n", t.getIntData());
		else if (t.getType() == Token::NUMBER_FLOAT)
			printf("Type: FLOAT | Val: %f\n", t.getFloatData());
		else if (t.getType() == Token::STRING)
			printf("Type: STR | Val: %s\n", t.getStrData().c_str());
		else if (t.getType() == Token::CURLY_START)
			printf("Type: CURLY_START \n");
		else if (t.getType() == Token::CURLY_END)
			printf("Type: CURLY_END \n");
		else if (t.getType() == Token::EQUALS)
			printf("Type: EQUALS \n");
		else if (t.getType() == Token::SEMICOLON)
			printf("Type: SEMICOLON \n");
		else if (t.getType() == Token::NULLTOKEN)
			printf("Type: NULLTOKEN \n");
	}
}
