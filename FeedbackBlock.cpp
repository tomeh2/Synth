#include "FeedbackBlock.h"

void FeedbackBlock::insert(Block* block)
{
	this->block = block;
}

void FeedbackBlock::process(float* buffer, unsigned int bufSize)
{
	for (size_t i = 0; i < bufSize; i++)
	{
		this->block->process(&blockOutput, 1);
		buffer[i] = blockOutput;
	}
}

void FeedbackBlock::process(float* inBuffer, float* outBuffer, unsigned int bufSize)
{
	for (size_t i = 0; i < bufSize; i++)
	{
		this->block->process(&blockOutput, 1);
		outBuffer[i] = blockOutput;
	}
}
