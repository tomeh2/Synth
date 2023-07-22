#include "SerialBlock.h"
#include "Algorithm.h"
#include "SineOscillator.h"
#include "PatchFileLoader.h"
#include "Patch.h"
#include "Channel.h"
#include "AudioEngine.h"
#include "FileOutputInterface.h"
#include "FileInputInterface.h"

#include <iostream>
#include <map>

#define BUF_SIZE 100000


int main(int argc, char** argv)
{
	std::map<std::string, Patch*> patches;
	PatchFileLoader::loadPatchFile("C:/Users/PC/Desktop/test.patch", &patches);

	patches.at("patch_1")->printInfo();
	printf("\n");
	patches.at("patch_2")->printInfo();

	FileOutputInterface fout("C:/users/pc/desktop/data.raw");
	FileInputInterface fin("C:/users/pc/desktop/midis/test.mid");
	AudioEngine a(patches.at("patch_1"), 16, 32, &fin, &fout, (size_t) 128, 44100);

	a.start();
}