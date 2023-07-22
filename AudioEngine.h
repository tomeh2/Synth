#pragma once

#include "Patch.h"
#include "Channel.h"
#include "OutputInterface.h"
#include "InputInterface.h"

class AudioEngine
{
private:
	std::vector<Channel*> channels;
	OutputInterface* out;
	InputInterface* in;

	size_t bufSize;
	int sampleRate;
	int usPerTick;
	int usPerQuarter;

	void mainLoop();
public:
	AudioEngine(Patch* defaultPatch, int numChannels, int maxVoicesPerChannel, InputInterface* in, OutputInterface* out, size_t bufSize, int sampleRate);
	~AudioEngine();

	void start();

	void tempGenSamples(float* buffer, size_t bufSize);
};

