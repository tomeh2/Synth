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

	union Data
	{
		int intData;
		float floatData;
		char strData[64];

		Data() {}
		~Data() {}
	} data;
public:
	Token(TokenType type) { tokenType = type; }
	Token(Token& token) 
	{ 
		tokenType = token.tokenType;
		
		if (tokenType == NUMBER_INT)
			data.intData = token.data.intData;
		else if (tokenType == NUMBER_FLOAT)
			data.floatData = token.data.floatData;
		else if (tokenType == STRING)
			strcpy(data.strData, token.data.strData);
	}

	int getIntData() { return data.intData; }
	float getFloatData() { return data.floatData; }
	std::string getStrData() { return data.strData; }
	TokenType getType() { return tokenType; }
	void setType(TokenType type) { tokenType = type; }
	void setIntData(int intData) { data.intData = intData; }
	void setFloatData(float floatData) { data.floatData = floatData; }
	void setStringData(std::string strData) { strcpy(data.strData, strData.c_str()); }
};