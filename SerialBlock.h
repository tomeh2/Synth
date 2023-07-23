#pragma once

#include "Block.h"

#include <vector>

class SerialBlock : public Block
{
private:
	std::vector<Block*> blocks;
public:
	void insert(Block* block);
	void process(float* buffer, unsigned int bufSize);
	void process(float* inBuffer, float* outBuffer, unsigned int bufSize);
};