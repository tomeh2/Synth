#include "ParallelBlock.h"

void ParallelBlock::process(float* buffer, unsigned int bufSize)
{
	float* tempBuf1 = new float[bufSize];
	float* tempBuf2 = new float[bufSize];

	memset(tempBuf2, 0, sizeof(float) * bufSize);

	for (std::vector<Block*>::iterator it = this->blocks.begin(); it != this->blocks.end(); it++)
	{
		(*it)->process(buffer, tempBuf1, bufSize);

		for (int i = 0; i < bufSize; i++)
		{
			tempBuf2[i] += tempBuf1[i];
		}
	}

	memcpy(buffer, tempBuf2, sizeof(float) * bufSize);

	delete[] tempBuf1;
	delete[] tempBuf2;
}

void ParallelBlock::insert(Block* block)
{
	this->blocks.insert(this->blocks.begin(), block);
}