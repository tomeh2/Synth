#include "Operator.h"

Operator::~Operator()
{
	delete this->oscillator;
	delete this->envGen;
}

void Operator::trigger()
{
	if (this->envGen != nullptr)
		this->envGen->trigger();
}

void Operator::release()
{
	if (this->envGen != nullptr)
		this->envGen->release();
}

void Operator::process(float* buffer, unsigned int bufSize)
{
	this->oscillator->process(buffer, bufSize);

	if (this->envGen != nullptr)
		this->envGen->process(buffer, bufSize);
}

void Operator::setBaseFrequency(float baseFreq)
{
	this->oscillator->setBaseFreq(baseFreq);
}

bool Operator::isActive()
{
	if (this->envGen == nullptr)
		return false;
	return this->envGen->isActive();
}
