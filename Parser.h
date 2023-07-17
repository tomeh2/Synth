#pragma once

#include "Token.h"
#include "Patch.h"

#include <vector>
#include <map>

class Parser
{
private:
	static int expect(Token::TokenType expectedType, Token* token);
	static int accept(std::vector<Token*>* tokens, Token::TokenType acceptedType);
	static int accept(std::vector<Token*>* tokens, Token::TokenType acceptedType, void* value);
	static int nextSym();

	static int blockPatch(std::vector<Token*>* tokens, std::map<std::string, Patch*>* patches);
	static int blockOperator(std::vector<Token*>* tokens, Patch* patch);
	static int statementString(std::vector<Token*>* tokens, std::string* lvalue, std::string* rvalue);
	static int statementFloat(std::vector<Token*>* tokens, std::string* lvalue, float* rvalue);
	static int statementInt(std::vector<Token*>* tokens, std::string* lvalue, int* rvalue);
public:
	static int parse(std::vector<Token*>* tokens, std::map<std::string, Patch*>* patches);
};

