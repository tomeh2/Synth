#pragma once

#include "Patch.h"
#include "Channel.h"
#include "OutputInterface.h"

class AudioEngine
{
private:
	std::vector<Channel*> channels;
	OutputInterface* out;

	size_t bufSize;

	void mainLoop();
public:
	AudioEngine(Patch* defaultPatch, int numChannels, int maxVoicesPerChannel, OutputInterface* out, size_t bufSize);
	~AudioEngine();

	void start();

	void tempGenSamples(float* buffer, size_t bufSize);
};

