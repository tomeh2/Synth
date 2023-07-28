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
	int BPM;
	float* channelPanL;		//0.0 - Center | -1.0 - Left | 1.0 - Right
	float* channelPanR;		//0.0 - Center | -1.0 - Left | 1.0 - Right

	void mainLoop();
	void calcUsPerTick();
	float linToExpVolume(float val);
public:
	AudioEngine(Patch* defaultPatch, int numChannels, int maxVoicesPerChannel, InputInterface* in, OutputInterface* out, size_t bufSize, int sampleRate);
	~AudioEngine();

	void start();

	void tempGenSamples(float* bufferL ,float* bufferR, size_t bufSize);
};

