#pragma once

#include <string>

class Token
{
public:
	enum TokenType
	{
		CURLY_START,
		CURLY_END,
		SEMICOLON,
		EQUALS,
		NUMBER_FLOAT,
		NUMBER_INT,
		STRING,
		NULLTOKEN
	};
private:
	TokenType tokenType;

	std::string data;
public:
	Token(TokenType type) { tokenType = type; }
	Token(Token& token) 
	{ 
		tokenType = token.tokenType;
	}
	std::string getData() { return data; }
	TokenType getType() { return tokenType; }
	void setType(TokenType type) { tokenType = type; }
	void setData(std::string strData) { data = strData; }
};