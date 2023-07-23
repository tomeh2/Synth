#include "SerialBlock.h"

void SerialBlock::process(float* buffer, unsigned int bufSize)
{
	for (std::vector<Block*>::iterator it = this->blocks.begin(); it != this->blocks.end(); it++)
	{
		(*it)->process(buffer, bufSize);
	}
}

void SerialBlock::process(float* inBuffer, float* outBuffer, unsigned int bufSize)
{
	memcpy(outBuffer, inBuffer, sizeof(float) * bufSize);
	for (std::vector<Block*>::iterator it = this->blocks.begin(); it != this->blocks.end(); it++)
	{
		(*it)->process(outBuffer, bufSize);
	}
}

void SerialBlock::insert(Block* block)
{
	this->blocks.insert(this->blocks.begin(), block);
}