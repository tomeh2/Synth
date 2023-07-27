#pragma once

#include "Block.h"
#include "EnvelopeGenerator.h"
#include "SineOscillator.h"

class Operator : public Block
{
private:
	SineOscillator* oscillator;
	EnvelopeGenerator* envGen;
public:
	Operator(SineOscillator* oscillator, EnvelopeGenerator* envGen) : oscillator(oscillator), envGen(envGen) {};
	~Operator();

	void trigger();
	void release();

	void process(float* buffer, unsigned int bufSize);
	void process(float* inBuffer, float* outBuffer, unsigned int bufSize) { return; }
	void setBaseFrequency(float baseFreq);

	bool isActive();
};

