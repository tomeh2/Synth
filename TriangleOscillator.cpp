#include "TriangleOscillator.h"

#define _USE_MATH_DEFINES
#include <math.h>

TriangleOscillator::TriangleOscillator(float relFreq, float modIndex, float amplitude)
{
	this->relFreq = relFreq;
	this->modIndex = modIndex;
	this->amplitude = amplitude;
	this->baseFreq = 440.f;
	this->time = 0.f;
}

void TriangleOscillator::process(float* buffer, unsigned int bufSize)
{
	float temp;
	for (unsigned int i = 0; i < bufSize; i++)
	{
		temp = buffer[i];
		buffer[i] = amplitude * (time < M_PI ? 2.f * time / M_PI - 1.f : -2.f * time / M_PI + 3.f);
		time += 2.f * M_PI * (this->baseFreq * this->relFreq + (temp * this->modIndex * this->baseFreq * this->relFreq)) / 44100.f;

		if (time > 2 * M_PI)
			time -= 2 * M_PI;
	}
}

void TriangleOscillator::process(float* inBuffer, float* outBuffer, unsigned int bufSize)
{
	for (unsigned int i = 0; i < bufSize; i++)
	{
		outBuffer[i] = amplitude * (time < M_PI ? 2.f * time / M_PI - 1.f : -2.f * time / M_PI + 3.f);
		time += 2.f * M_PI * (this->baseFreq * this->relFreq + (inBuffer[i] * this->modIndex * this->baseFreq * this->relFreq)) / 44100.f;

		if (time > 2 * M_PI)
			time -= 2 * M_PI;
	}
}

void TriangleOscillator::setBaseFreq(float baseFreq)
{
	this->baseFreq = baseFreq;
}
