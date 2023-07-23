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

	delete[] tempBuf;
}

void Channel::keyDown(int keyNum)
{
	if (this->activeVoices.find(keyNum) == this->activeVoices.end())
	{
		Voice* v = this->freeVoices.top();
		this->freeVoices.pop();



		v->keyDown(keyNum);
		this->activeVoices.insert(std::pair<int, Voice*>(keyNum, v));
	}
}

void Channel::keyUp(int keyNum)
{
	if (this->activeVoices.find(keyNum) != this->activeVoices.end())
	{
		Voice* v = this->activeVoices.at(keyNum);
		v->keyUp();
		this->activeVoices.erase(keyNum);

		// TEMPORARY
		this->freeVoices.push(v);
	}
}





