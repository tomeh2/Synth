#pragma once

#include "Block.h"

#include <string>
#include <vector>

class Algorithm : public Block
{
private:
	Block* algorithmBlock = nullptr;
	
	Block* create_rec(std::string substructure, std::vector<Block*>* blocks, int* block);
public:
	void process(float* buffer, unsigned int bufSize);
	void create(std::string structure);
};