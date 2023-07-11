#include "SerialBlock.h"

void SerialBlock::process(float* inBuffer, float* outBuffer, unsigned int bufSize)
{
	float* tempBuf = inBuffer;
	for (std::vector<Block*>::iterator it = this->blocks.begin(); it != this->blocks.end(); it++)
	{
		(*it)->process(tempBuf, outBuffer, bufSize);
		tempBuf = outBuffer;
	}
}

void SerialBlock::insert(Block* block)
{
	this->blocks.push_back(block);
}