#include "SineOscillator.h"

#include <math.h>

SineOscillator::SineOscillator(float relFreq, float modIndex, float amplitude)
{
	this->relFreq = relFreq;
	this->modIndex = modIndex;
	this->amplitude = amplitude;
	this->baseFreq = 440.f;
	this->time = 0.f;
}

void SineOscillator::process(float* buffer, unsigned int bufSize)
{
	float temp;
	for (unsigned int i = 0; i < bufSize; i++)
	{
		temp = buffer[i];
		buffer[i] = amplitude * sin(time);
		time += 2.f * 3.1415f * (this->baseFreq * this->relFreq + temp * this->modIndex) / 44100.f;

		if (time > 2 * 3.1415f)
			time -= 2 * 3.1415f;
	}
}

void SineOscillator::process(float* inBuffer, float* outBuffer, unsigned int bufSize)
{
	float temp;
	for (unsigned int i = 0; i < bufSize; i++)
	{
		temp = inBuffer[i];
		outBuffer[i] = amplitude * sin(time);
		time += 2.f * 3.1415f * (this->baseFreq * this->relFreq + temp * this->modIndex) / 44100.f;

		if (time > 2 * 3.1415f)
			time -= 2 * 3.1415f;
	}
}

void SineOscillator::setBaseFreq(float baseFreq)
{
	this->baseFreq = baseFreq;
}
