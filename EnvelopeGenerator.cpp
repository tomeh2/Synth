#include "EnvelopeGenerator.h"

#include <math.h>

#define DELTA_T 0.01f

EnvelopeGenerator::~EnvelopeGenerator()
{
	for (size_t i = 0; i < this->envSegments.size(); i++)
	{
		delete this->envSegments.at(i);
	}
}

void EnvelopeGenerator::addSegment(float rate, float target, float offset, SegmentType type)
{
	EnvelopeSegment* seg = new EnvelopeSegment;
	seg->rate = rate;
	seg->target = target;
	seg->offset = offset;
	seg->segType = type;
	this->envSegments.insert(this->envSegments.end(), seg);
}

void EnvelopeGenerator::trigger()
{
	int temp = this->currSegmentIndex;
	this->currSegmentIndex = 0;
	this->currSegment = this->envSegments.at(this->currSegmentIndex);

	if (temp == -1)
		this->t = 0.f;
	else
		this->t = envValToTime(this->currValue);
}

void EnvelopeGenerator::release()
{
	this->currSegmentIndex = this->envSegments.size() - 2;
	advanceSegment();
}

float EnvelopeGenerator::envValToTime(float val)
{
	float t = 0.f;
	if (this->currSegment->segType == SegmentType::EXP)
	{
		if (this->currSegment->rate > 0.f)
		{
			t = log(val + 1.f) / this->currSegment->rate;
		}
		else
		{
			t = log(val - this->currSegment->target) / this->currSegment->rate;
		}
	}
	else
	{
		t = 0.f;
	}
	return t;
}

void EnvelopeGenerator::advanceSegment()
{
	this->currSegmentIndex++;

	if (this->currSegmentIndex >= this->envSegments.size())
	{
		this->currSegmentIndex = -1;
		this->currSegment = nullptr;
		return;
	}
	else
	{
		this->currSegment = this->envSegments.at(this->currSegmentIndex);
		this->t = envValToTime(this->currValue);
	}
}

//PRE-COMPUTE THE ENVELOPE INTO A TABLE IN THE FUTURE TO AVOID MASSIVE PERFORMANCE HITS
void EnvelopeGenerator::process(float* buffer, size_t bufSize)
{
	for (size_t i = 0; i < bufSize; i++)
	{
		if (this->currSegmentIndex == -1)
		{
			buffer[i] = 0.f;
			continue;
		}
		else
			buffer[i] *= this->currValue;


		if (this->currSegment->segType == SegmentType::FLAT)
		{
			this->currValue = this->currSegment->target;
		}
		else if (this->currSegment->segType == SegmentType::EXP)
		{
			this->t += DELTA_T;
			this->currValue = exp(this->currSegment->rate * this->t);

			if (this->currSegment->rate > 0.f)
			{
				this->currValue -= 1.f;

				if (this->currValue >= this->currSegment->target)
				{
					advanceSegment();
				}
			}
			else
			{
				this->currValue += this->currSegment->target;

				if (this->currValue <= this->currSegment->target + 0.001f)
				{
					advanceSegment();
				}
			}
		}
		else if (this->currSegment->segType == SegmentType::LIN)
		{
			this->currValue += this->currSegment->rate;

			if (this->currSegment->rate > 0.f)
			{
				if (this->currValue >= this->currSegment->target)
				{
					advanceSegment();
				}
			}
			else
			{
				if (this->currValue <= this->currSegment->target)
				{
					advanceSegment();
				}
			}
		}
	}
}

bool EnvelopeGenerator::isActive()
{
	return this->currSegmentIndex != -1;
}
