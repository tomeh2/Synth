#include "AudioEngine.h"
#include "Logger.h"

AudioEngine::AudioEngine(Patch* defaultPatch, int numChannels, int maxVoicesPerChannel, InputInterface* in, OutputInterface* out, size_t bufSize, int sampleRate)
{
	this->in = in;
	this->out = out;
	this->bufSize = bufSize;
	this->sampleRate = sampleRate;
	this->BPM = 120;
	calcUsPerTick();

	char msg[256];
	sprintf(msg, "AudioEngine initialized");
	Logger::log(Logger::INFO, msg);

	sprintf(msg, "Buffer Size = %lld samples", bufSize);
	Logger::log(Logger::INFO, msg);

	sprintf(msg, "Sample Rate = %d", sampleRate);
	Logger::log(Logger::INFO, msg);

	sprintf(msg, "us Per Tick = %d", this->usPerTick);
	Logger::log(Logger::INFO, msg);

	for (int i = 0; i < numChannels; i++)
	{
		this->channels.push_back(new Channel(defaultPatch, maxVoicesPerChannel, i));
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

	delete[] tempBuf;
}

void AudioEngine::start()
{
	in->reset();
	mainLoop();
}

void AudioEngine::mainLoop()
{
	float* buffer = new float[this->bufSize];
	short* bufferShort = new short[this->bufSize];

	float tick = 0;

	for (int i = 0; i < 200000; i++)
	{
		smf::MidiEvent midiEvent;
		while ((midiEvent = this->in->getNextEvent()).tick <= (int) tick)
		{
			if (midiEvent.isNoteOn())
				this->channels[midiEvent.getChannel()]->keyDown(midiEvent.getKeyNumber());
			else if (midiEvent.isNoteOff())
				this->channels[midiEvent.getChannel()]->keyUp(midiEvent.getKeyNumber());
			else if (midiEvent.isTempo())
			{
				this->BPM = midiEvent.getTempoBPM();
				calcUsPerTick();
			}


			this->in->advance();
		}

		tempGenSamples(buffer, this->bufSize);

		for (int i = 0; i < this->bufSize; i++)
		{
			bufferShort[i] = (short) (buffer[i] * 2000);
		}

		this->out->write(bufferShort, this->bufSize);

		//char msg[256];
		//sprintf(msg, "Tick = %f", tick);
		//Logger::log(Logger::INFO, msg);

		tick += ((float)this->bufSize / this->sampleRate * 1000000.f) / this->usPerTick;
		//tick += 1;
	}

	delete[] buffer;
	delete[] bufferShort;
}

void AudioEngine::calcUsPerTick()
{
	this->usPerTick = 60000000 / (this->BPM * in->getTPQ());
}
