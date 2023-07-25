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
	static int accept(std::vector<Token*>* tokens, Token::TokenType expectedType, std::string value);
	static int nextSym();

	static int blockPatch(std::vector<Token*>* tokens, std::map<std::string, Patch*>* patches);
	static int blockOperator(std::vector<Token*>* tokens, Patch* patch); 
	static int blockEnvelope(std::vector<Token*>* tokens, Patch* patch); 
	static int blockSegments(std::vector<Token*>* tokens, Patch* patch, std::string currEnvelope, int currEnvelopeId); 
	static int statement(std::vector<Token*>* tokens, std::string* lvalue, std::string* rvalue);
public:
	static int parse(std::vector<Token*>* tokens, std::map<std::string, Patch*>* patches);
};

