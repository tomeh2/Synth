#pragma once

#include <vector>

#include "Block.h"

class EnvelopeGenerator : public Block
{
public:
	enum SegmentType
	{
		EXP,
		LIN,
		FLAT
	};
private:
	struct EnvelopeSegment
	{
		SegmentType segType;
		float rate;
		float target;
		float offset;
	};
	std::vector<EnvelopeSegment*> envSegments;
	EnvelopeSegment* currSegment;

	int currSegmentIndex = -1;
	float currValue = 0.f;
	float t = 0.f;

	float envValToTime(float val);
	void advanceSegment();
	void setSegment(int segmentIndex);
public:
	EnvelopeGenerator() {}
	~EnvelopeGenerator();
	void addSegment(float rate, float target, float offset, SegmentType type);

	void trigger();
	void release();

	void process(float* buffer, size_t bufSize);
	bool isActive();
};

