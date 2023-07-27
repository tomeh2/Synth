#pragma once

#include "MidiFile.h"
#include "InputInterface.h"

class FileInputInterface : public InputInterface
{
private:
	smf::MidiFile midiFile;

	int currEvent = 0;
public:
	FileInputInterface(const char* filename);

	smf::MidiEvent getNextEvent();
	void advance();
	void reset();
	int getTPQ();
	bool isActive();
};