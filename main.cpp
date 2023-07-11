#include "SerialBlock.h"
#include "Operator.h"
#include "SineOscillator.h"

#include <iostream>

#define BUF_SIZE 100000


int main(int argc, char** argv)
{
	float in[BUF_SIZE];
	float out[BUF_SIZE];

	for (int i = 0; i < BUF_SIZE; i++)
	{
		in[i] = 0.f;
	}

	short audioOut[BUF_SIZE];

	Operator op;
	op.create("c(2,1)");
	op.process(in, out, BUF_SIZE);

	for (int i = 0; i < BUF_SIZE; i++)
	{

		audioOut[i] = out[i] * 2000;
		//std::cout << audioOut[i] << " | ";
	}

	FILE* desc = nullptr;
	desc = fopen("C:\\Users\\PC\\Desktop\\data.raw", "wb");
	fwrite(audioOut, sizeof(short), BUF_SIZE, desc);
	fclose(desc);
}