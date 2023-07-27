#pragma once

#include "MidiEvent.h"

class InputInterface
{
public:
	virtual smf::MidiEvent getNextEvent() = 0;
	virtual void advance() {};
	virtual void reset() {};
	virtual int getTPQ() { return 0; };
	virtual bool isActive() { return false; };
};