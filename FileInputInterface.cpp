#include "FileInputInterface.h"

#include "MidiFile.h"
#include "Logger.h"

FileInputInterface::FileInputInterface(const char* filename)
{
	char msg[256];
	if (!this->midiFile.read(filename))
	{
		sprintf(msg, "Failed to open input MIDI file %s", filename);
		Logger::log(Logger::ERROR, msg);
		return;
	}
	sprintf(msg, "Successfully opened input MIDI file %s", filename);
	Logger::log(Logger::INFO, msg);

	sprintf(msg, "TPQ = %d", this->midiFile.getTicksPerQuarterNote());
	Logger::log(Logger::INFO, msg);

	sprintf(msg, "TRACKS = %d", this->midiFile.getTrackCount());
	Logger::log(Logger::INFO, msg);

	this->midiFile.joinTracks();
	reset();
}

smf::MidiEvent FileInputInterface::getNextEvent()
{
	return this->midiFile.getEvent(0, this->currEvent);
}

void FileInputInterface::advance()
{
	this->currEvent++;
}

void FileInputInterface::reset()
{
	this->currEvent = 0;
}

int FileInputInterface::getTPQ()
{
	return this->midiFile.getTicksPerQuarterNote();
}
