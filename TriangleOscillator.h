#pragma once

#include "Oscillator.h"

class TriangleOscillator : public Oscillator
{
private:
	float relFreq, modIndex, amplitude, time;
	float baseFreq;
public:
	TriangleOscillator(float relFreq, float modIndex, float amplitude);
	void process(float* buffer, unsigned int bufSize);
	void process(float* inBuffer, float* outBuffer, unsigned int bufSize);

	void setBaseFreq(float baseFreq);
};
