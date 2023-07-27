#include "SineOscillator.h"

#define _USE_MATH_DEFINES
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
		time += 2.f * M_PI * (this->baseFreq * this->relFreq + (temp * this->modIndex * this->baseFreq * this->relFreq)) / 44100.f;

		if (time > 2 * M_PI)
			time -= 2 * M_PI;
	}
}

void SineOscillator::process(float* inBuffer, float* outBuffer, unsigned int bufSize)
{
	for (unsigned int i = 0; i < bufSize; i++)
	{
		outBuffer[i] = amplitude * sin(time);
		time += 2.f * M_PI * (this->baseFreq * this->relFreq + (inBuffer[i] * this->modIndex * this->baseFreq * this->relFreq)) / 44100.f;

		if (time > 2 * M_PI)
			time -= 2 * M_PI;
	}
}

void SineOscillator::setBaseFreq(float baseFreq)
{
	this->baseFreq = baseFreq;
}
