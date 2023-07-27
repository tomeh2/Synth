#include "SquareOscillator.h"

SquareOscillator::SquareOscillator(float relFreq, float modIndex, float amplitude)
{
	this->relFreq = relFreq;
	this->modIndex = modIndex;
	this->amplitude = amplitude;
	this->baseFreq = 440.f;
	this->time = 0.f;
}

void SquareOscillator::process(float* buffer, unsigned int bufSize)
{
	float temp;
	for (unsigned int i = 0; i < bufSize; i++)
	{
		temp = buffer[i];
		buffer[i] = amplitude * (time > 3.1415f ? 1.f : -1.f);
		time += 2.f * 3.1415f * (this->baseFreq * this->relFreq + (temp * this->modIndex * this->baseFreq * this->relFreq)) / 44100.f;

		if (time > 2 * 3.1415f)
			time -= 2 * 3.1415f;
	}
}

void SquareOscillator::process(float* inBuffer, float* outBuffer, unsigned int bufSize)
{
	for (unsigned int i = 0; i < bufSize; i++)
	{
		outBuffer[i] = amplitude * (time > 3.1415f ? 1.f : -1.f);
		time += 2.f * 3.1415f * (this->baseFreq * this->relFreq + (inBuffer[i] * this->modIndex * this->baseFreq * this->relFreq)) / 44100.f;

		if (time > 2 * 3.1415f)
			time -= 2 * 3.1415f;
	}
}

void SquareOscillator::setBaseFreq(float baseFreq)
{
	this->baseFreq = baseFreq;
}
