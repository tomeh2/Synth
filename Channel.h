#pragma once

#include "Voice.h"

#include <stack>
#include <map>

class Channel
{
private:
	std::stack<Voice*> freeVoices;
	std::map<int, Voice*> activeVoices;
public:
	Channel(Patch* p, int maxVoices);

	void generateBlock(float* buffer, int bufSize);
	void keyDown(int keyNum);
	void keyUp(int keyNum);
};

