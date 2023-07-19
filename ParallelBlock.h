#pragma once

#include "Block.h"

#include <vector>

class ParallelBlock : public Block
{
private:
	std::vector<Block*> blocks;
public:
	void insert(Block* block);
	void process(float* buffer, unsigned int bufSize);
};

