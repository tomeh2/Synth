#pragma once

#include "Algorithm.h"
#include "Block.h"

class Voice : public Block
{
private:
	Algorithm algorithm;
public:
	Voice(Patch* p)
	{
		algorithm.create(p);
	}

	void generateBlock(float* buffer, int bufSize);
	void keyDown(int keyNum);
	void keyUp();
};


