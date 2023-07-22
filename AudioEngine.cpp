#include "AudioEngine.h"

AudioEngine::AudioEngine(Patch* defaultPatch, int numChannels, int maxVoicesPerChannel, OutputInterface* out, size_t bufSize)
{
	this->out = out;
	this->bufSize = bufSize;

	for (int i = 0; i < numChannels; i++)
	{
		this->channels.push_back(new Channel(defaultPatch, maxVoicesPerChannel));
	}
}

AudioEngine::~AudioEngine()
{
	int numChannels = this->channels.size();
	for (int i = 0; i < numChannels; i++)
	{
		delete this->channels.at(i);
	}
}

void AudioEngine::tempGenSamples(float* buffer, size_t bufSize)
{
	float* tempBuf = new float[bufSize];

	memset(tempBuf, 0, sizeof(float) * bufSize);
	memset(buffer, 0, sizeof(float) * bufSize);

	for (auto it = this->channels.begin(); it != this->channels.end(); it++)
	{
		(*it)->generateBlock(tempBuf, bufSize);

		for (int i = 0; i < bufSize; i++)
		{
			buffer[i] += tempBuf[i];
		}
	}
}

void AudioEngine::start()
{
	mainLoop();
}

void AudioEngine::mainLoop()
{
	float* buffer = new float[this->bufSize];
	short* bufferShort = new short[this->bufSize];

	for (int i = 0; i < 512; i++)
	{
		if (i == 10)
		{
			this->channels.at(0)->keyDown(42);
		}

		if (i == 400)
		{
			this->channels.at(0)->keyUp(42);
		}

		tempGenSamples(buffer, this->bufSize);

		for (int i = 0; i < this->bufSize; i++)
		{
			bufferShort[i] = (short) (buffer[i] * 2000);
		}

		this->out->write(bufferShort, this->bufSize);
	}

	delete[] buffer;
	delete[] bufferShort;
}