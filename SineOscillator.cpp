#include "SineOscillator.h"

#include <math.h>

SineOscillator::SineOscillator(float frequency, float modIndex, float amplitude)
{
	this->frequency = frequency;
	this->modIndex = modIndex;
	this->amplitude = amplitude;
	this->time = 0.f;
}

void SineOscillator::process(float* buffer, unsigned int bufSize)
{
	float temp;
	for (unsigned int i = 0; i < bufSize; i++)
	{
		temp = buffer[i];
		buffer[i] = amplitude * sin(time);
		time += 2.f * 3.1415f * (frequency + temp * this->modIndex) / 44100.f;

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
		time += 2.f * 3.1415f * (frequency + temp * this->modIndex) / 44100.f;

		if (time > 2 * 3.1415f)
			time -= 2 * 3.1415f;
	}
}
