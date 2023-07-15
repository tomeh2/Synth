#pragma once

#include "Block.h"

class SineOscillator : public Block
{
private:
	float frequency, modIndex, amplitude, time;
public:
	SineOscillator(float frequency, float modIndex, float amplitude);
	void process(float* buffer, unsigned int bufSize);
};

