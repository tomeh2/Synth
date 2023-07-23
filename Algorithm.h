#pragma once

#include "Block.h"
#include "Patch.h"
#include "SineOscillator.h"
#include "Tokenizer.h"

#include <string>
#include <vector>
#include <stack>

class Algorithm : public Block
{
private:
	Block* algorithmBlock = nullptr;
	std::vector<SineOscillator*> operators;
	
	Block* create_rec(std::vector<Token*>* tokens, std::vector<Block*>* blocks, std::stack<Token*>* tokenStack, int* tokenIndex);
	void createOperators(Patch* patch, std::vector<Block*>* blocks);
public:
	void process(float* buffer, unsigned int bufSize);
	void create(Patch* patch);

	void setBaseFrequency(float freq);
};