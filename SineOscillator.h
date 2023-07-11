#pragma once

#include "Block.h"

class SineOscillator : public Block
{
private:
	float frequency, amplitude, time;
public:
	SineOscillator(float frequency, float amplitude);
	void process(float* inBuffer, float* outBuffer, unsigned int bufSize);
};

