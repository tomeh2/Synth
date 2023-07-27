#include "Voice.h"

void Voice::generateBlock(float* buffer, int bufSize)
{
	this->algorithm.process(buffer, bufSize);
}

void Voice::keyDown(int keyNum)
{
	this->algorithm.trigger(pow(1.059463f, keyNum - 69) * 440.0f);
}

void Voice::keyUp()
{
	this->algorithm.release();
}

bool Voice::isActive()
{
	return this->algorithm.isActive();
}

