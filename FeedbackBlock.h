#pragma once

#include "Block.h"

class FeedbackBlock : public Block
{
private:
	Block* block;

	float blockOutput = 0.f;
public:
	void insert(Block* block);
	void process(float* buffer, unsigned int bufSize);
};

