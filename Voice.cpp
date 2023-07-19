#include "Voice.h"

void Voice::generateBlock(float* buffer, int bufSize)
{
	this->algorithm.process(buffer, bufSize);
}

void Voice::keyDown(int keyNum)
{

}

void Voice::keyUp()
{

}

