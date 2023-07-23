#pragma once

#include "Voice.h"

#include <stack>
#include <map>

class Channel
{
private:
	std::stack<Voice*> freeVoices;
	std::map<int, Voice*> activeVoices;

	int chNum;
public:
	Channel(Patch* p, int maxVoices, int chNum);

	void generateBlock(float* buffer, int bufSize);
	void keyDown(int keyNum);
	void keyUp(int keyNum);
};

