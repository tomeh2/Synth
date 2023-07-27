#include "Channel.h"
#include "Logger.h"

Channel::Channel(Patch* p, int maxVoices, int chNum)
{
	char msg[256];

	this->chNum = chNum;

	for (int i = 0; i < maxVoices; i++)
	{
		this->freeVoices.push(new Voice(p));
	}
	this->volume = 1.f;

	sprintf(msg, "Channel %d initialized", chNum);
	Logger::log(Logger::INFO, msg);
}

void Channel::generateBlock(float* buffer, int bufSize)
{
	float* tempBuf = new float[bufSize];

	memset(buffer, 0, sizeof(float) * bufSize);
	for (auto it = this->activeVoices.begin(); it != this->activeVoices.end(); it++)
	{
		memset(tempBuf, 0, sizeof(float) * bufSize);
		(*it).second->generateBlock(tempBuf, bufSize);

		for (int i = 0; i < bufSize; i++)
		{
			buffer[i] += tempBuf[i];
		}
	}

	for (int i = 0; i < bufSize; i++)
	{
		buffer[i] *= this->volume;
	}

	freeInactiveVoices();

	delete[] tempBuf;
}

void Channel::keyDown(int keyNum)
{
	std::map<int, Voice*>::iterator it = this->activeVoices.begin();
	if ((it = this->activeVoices.find(keyNum)) == this->activeVoices.end())
	{
		Voice* v = this->freeVoices.top();
		this->freeVoices.pop();

		v->keyDown(keyNum);
		this->activeVoices.insert(std::pair<int, Voice*>(keyNum, v));
	}
	else
	{
		it->second->keyDown(keyNum);
	}
}

void Channel::keyUp(int keyNum)
{
	if (this->activeVoices.find(keyNum) != this->activeVoices.end())
	{
		Voice* v = this->activeVoices.at(keyNum);
		v->keyUp();
	}
}

void Channel::freeInactiveVoices()
{
	for (auto it = this->activeVoices.cbegin(); it != this->activeVoices.cend();)
	{
		Voice* v = it->second;
		if (!v->isActive())
		{
			this->activeVoices.erase(it++);
			this->freeVoices.push(v);
		}
		else
			it++;
	}
}

void Channel::setVolume(float vol)
{
	if (vol >= 0.f && vol <= 1.f)
	{
		this->volume = vol;
	}
}





