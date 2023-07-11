#pragma once

#include "Block.h"

#include <string>
#include <vector>

class Operator : public Block
{
private:
	Block* operatorBlock;
	
	Block* create_rec(std::string substructure, std::vector<Block*>* blocks, int* block);
public:
	void process(float* inBuffer, float* outBuffer, unsigned int bufSize);
	void create(std::string structure);
};