#pragma once

#include "Block.h"

class SineOscillator : public Block
{
private:
	float relFreq, modIndex, amplitude, time;
	float baseFreq;
public:
	SineOscillator(float relFreq, float modIndex, float amplitude);
	void process(float* buffer, unsigned int bufSize);
	void process(float* inBuffer, float* outBuffer, unsigned int bufSize);

	void setBaseFreq(float baseFreq);
};

