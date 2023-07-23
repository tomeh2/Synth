#include "Tokenizer.h"

Tokenizer::Tokenizer(FILE* file)
{
	this->file = file;
	this->str = "";
}

Tokenizer::Tokenizer(std::string str)
{
	this->file = nullptr;
	this->str = str;
}

int Tokenizer::isEOF()
{
	if (this->file != nullptr)
		return feof(this->file);
	return 0;
}

int Tokenizer::isEOS()
{
	if (this->str.compare("") != 0)
		return strIndex < this->str.size() ? 0 : 1;
	return 0;
}

void Tokenizer::movePointer(int val)
{
	if (this->file != nullptr)
		fseek(file, val, SEEK_CUR);
	else
		this->strIndex += val;
}

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
	return (c >= 65 && c <= 90 || c >= 97 && c <= 122 || c == '_' || c == '(' || c == ')' || c == ',') ? true : false;
}



int Tokenizer::getNextToken(Token* t)
{
	bool done = false;

	char readChar;
	std::string tokenVal = "";
	bool first = true;
	while (!isEOF() && !isEOS() && !done)
	{
		readChar = getNextChar();

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
			movePointer(-1);
			done = true;
		}
		else if (t->getType() == Token::STRING && !isAlpha(readChar) && !isNumeric(readChar))
		{
			movePointer(-1);
			done = true;
		}
		else
		{
			tokenVal.insert(tokenVal.end(), readChar);
		}
	}

	if (t->getType() == Token::NUMBER_INT)
		t->setData(tokenVal);
	else if (t->getType() == Token::NUMBER_FLOAT)
		t->setData(tokenVal);
	else if (t->getType() == Token::STRING)
	{
		//tokenVal.insert(tokenVal.end(), '\0');
		t->setData(tokenVal);
	}

	if (isEOF() || isEOS())
		return -1;
	else
		return 0;
}

char Tokenizer::getNextChar()
{
	if (this->file != nullptr)
	{
		return fgetc(this->file);
	}
	else
		return this->str.at(this->strIndex++);
}

void Tokenizer::tokenize(std::vector<Token*>* tokens)
{
	this->strIndex = 0;

	Token* t = new Token(Token::NULLTOKEN);
	while (getNextToken(t) != -1)
	{
		if (t->getType() == Token::NULLTOKEN)
			delete t;
		else
			tokens->insert(tokens->end(), t);
		t = new Token(Token::NULLTOKEN);
	}
}