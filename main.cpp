#include "SerialBlock.h"
#include "Algorithm.h"
#include "SineOscillator.h"
#include "PatchFileLoader.h"
#include "Patch.h"
#include "Channel.h"
#include "AudioEngine.h"
#include "FileOutputInterface.h"

#include <iostream>
#include <map>

#define BUF_SIZE 100000


int main(int argc, char** argv)
{
	float in[BUF_SIZE];

	for (int i = 0; i < BUF_SIZE; i++)
	{
		in[i] = 0.f;
	}

	short audioOut[BUF_SIZE];

	std::map<std::string, Patch*> patches;
	PatchFileLoader::loadPatchFile("C:/Users/PC/Desktop/test.patch", &patches);

	patches.at("patch_1")->printInfo();
	printf("\n");
	patches.at("patch_2")->printInfo();

	FileOutputInterface fout("C:/users/pc/desktop/data.raw");
	AudioEngine a(patches.at("patch_1"), 16, 32, &fout, 256);

	a.start();
}