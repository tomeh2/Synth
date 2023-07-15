#include "SerialBlock.h"

void SerialBlock::process(float* buffer, unsigned int bufSize)
{
	for (std::vector<Block*>::iterator it = this->blocks.begin(); it != this->blocks.end(); it++)
	{
		(*it)->process(buffer, bufSize);
	}
}

void SerialBlock::insert(Block* block)
{
	this->blocks.insert(this->blocks.begin(), block);
}