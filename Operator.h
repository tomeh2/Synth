#pragma once

#include "Block.h"
#include "EnvelopeGenerator.h"
#include "Oscillator.h"

class Operator : public Oscillator
{
private:
	Oscillator* oscillator;
	EnvelopeGenerator* envGen;
public:
	Operator(Oscillator* oscillator, EnvelopeGenerator* envGen) : oscillator(oscillator), envGen(envGen) {};
	~Operator();

	void trigger();
	void release();

	void process(float* buffer, unsigned int bufSize);
	void process(float* inBuffer, float* outBuffer, unsigned int bufSize) { return; }
	void setBaseFrequency(float baseFreq);

	bool isActive();
};

