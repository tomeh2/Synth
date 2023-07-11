#include "SineOscillator.h"

#include <math.h>

SineOscillator::SineOscillator(float frequency, float amplitude)
{
	this->frequency = frequency;
	this->amplitude = amplitude;
	this->time = 0.f;
}

void SineOscillator::process(float* inBuffer, float* outBuffer, unsigned int bufSize)
{
	for (unsigned int i = 0; i < bufSize; i++)
	{
		outBuffer[i] = amplitude * sin(time);
		time += 2.f * 3.1415f * (frequency + inBuffer[i] * 10.f) / 44100.f;

		if (time > 2 * 3.1415f)
			time = fmod(time, 2 * 3.1415f);
	}
}