#include "SerialBlock.h"
#include "Algorithm.h"
#include "SineOscillator.h"

#include <iostream>

#define BUF_SIZE 100000


int main(int argc, char** argv)
{
	float in[BUF_SIZE];

	for (int i = 0; i < BUF_SIZE; i++)
	{
		in[i] = 0.f;
	}

	short audioOut[BUF_SIZE];

	Algorithm op;
	op.create("c(1,2,3)");
	op.process(in, BUF_SIZE);

	for (int i = 0; i < BUF_SIZE; i++)
	{

		audioOut[i] = in[i] * 2000;
		//std::cout << audioOut[i] << " | ";
	}

	FILE* desc = nullptr;
	desc = fopen("C:\\Users\\PC\\Desktop\\data.raw", "wb");
	fwrite(audioOut, sizeof(short), BUF_SIZE, desc);
	fclose(desc);
}