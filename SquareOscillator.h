#pragma once

#include "Oscillator.h"

class SquareOscillator : public Oscillator
{
private:
	float relFreq, modIndex, amplitude, time;
	float baseFreq;
public:
	SquareOscillator(float relFreq, float modIndex, float amplitude);
	void process(float* buffer, unsigned int bufSize);
	void process(float* inBuffer, float* outBuffer, unsigned int bufSize);

	void setBaseFreq(float baseFreq);
};

