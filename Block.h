#pragma once

/*
	Base class from which any element that needs to be inserted into the processing chain needs to inherit
*/

class Block
{
public:
	virtual void process(float* buffer, unsigned int bufSize) { return; };
	virtual void process(float* inBuffer, float* outBuffer, unsigned int bufSize) { return; };
};

