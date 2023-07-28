#include "AudioEngine.h"
#include "Logger.h"

AudioEngine::AudioEngine(Patch* defaultPatch, int numChannels, int maxVoicesPerChannel, InputInterface* in, OutputInterface* out, size_t bufSize, int sampleRate)
{
	this->in = in;
	this->out = out;
	this->bufSize = bufSize;
	this->sampleRate = sampleRate;
	this->BPM = 120;
	this->channelPanL = new float[numChannels];
	this->channelPanR = new float[numChannels];
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
		this->channelPanL[i] = 1.f;
		this->channelPanR[i] = 1.f;
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
	delete[] channelPanL;
	delete[] channelPanR;
}

void AudioEngine::tempGenSamples(float* bufferL, float* bufferR, size_t bufSize)
{
	float* tempBuf = new float[bufSize];

	memset(tempBuf, 0, sizeof(float) * bufSize);
	memset(bufferL, 0, sizeof(float) * bufSize);
	memset(bufferR, 0, sizeof(float) * bufSize);

	int j = 0;
	for (auto it = this->channels.begin(); it != this->channels.end(); it++)
	{
		(*it)->generateBlock(tempBuf, bufSize);

		for (int i = 0; i < bufSize; i++)
		{
			bufferL[i] += tempBuf[i] * this->channelPanL[j];
			bufferR[i] += tempBuf[i] * this->channelPanR[j];
		}
		j++;
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
	char msg[256];
	float* bufferL = new float[this->bufSize];
	float* bufferR = new float[this->bufSize];
	short* bufferShort = new short[2 * this->bufSize];

	float tick = 0;
	while (this->in->isActive())
	{
		smf::MidiEvent midiEvent;
		while ((midiEvent = this->in->getNextEvent()).tick <= (int)tick)
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
			else if (midiEvent.isController())
			{
				switch (midiEvent.getP1())				// VOLUME CONTROL
				{
				case 0x07:
					sprintf(msg, "[CONTROLLER] Channel: %d | Set Volume: %d", midiEvent.getChannel(), midiEvent.getP2());
					Logger::log(Logger::INFO, msg);

					this->channels[midiEvent.getChannel()]->setVolume(linToExpVolume(midiEvent.getP2() / 127.f));

					// TEMPORARILY TURN OFF PERCUSSION INSTRUMENTS
					if (midiEvent.getChannel() == 9)
						this->channels[midiEvent.getChannel()]->setVolume(0.f);
					break;
				case 0x0A:
					sprintf(msg, "[CONTROLLER] Channel: %d | Pan: %d", midiEvent.getChannel(), midiEvent.getP2());
					Logger::log(Logger::INFO, msg);

					this->channelPanL[midiEvent.getChannel()] = midiEvent.getP2() < 64 ? 1.f : -1.f / 64.f * midiEvent.getP2() + 2.f;
					this->channelPanR[midiEvent.getChannel()] = midiEvent.getP2() > 64 ? 1.f : 1.f / 64.f * midiEvent.getP2();
					break;
				default:
					break;
				}
			}
			else if (midiEvent.getCommandByte() == 0 && midiEvent.getP1() == 0)
				break;


			this->in->advance();
		}

		tempGenSamples(bufferL, bufferR, this->bufSize);

		for (int i = 0; i < 2 * this->bufSize; i += 2)
		{
			bufferShort[i] = (short) (bufferL[i >> 1] * 2000);
			bufferShort[i + 1] = (short) (bufferR[i >> 1] * 2000);
		}

		this->out->write(bufferShort, this->bufSize * 2);

		//
		//sprintf(msg, "Tick = %f", tick);
		//Logger::log(Logger::INFO, msg);

		tick += ((float)this->bufSize / this->sampleRate * 1000000.f) / this->usPerTick;
		//tick += 1;
	}

	delete[] bufferL;
	delete[] bufferR;
	delete[] bufferShort;
}

void AudioEngine::calcUsPerTick()
{
	this->usPerTick = 60000000 / (this->BPM * in->getTPQ());
}

float AudioEngine::linToExpVolume(float val)
{
	return val * val;
}
