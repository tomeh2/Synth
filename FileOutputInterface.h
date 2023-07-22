#pragma once

#include "OutputInterface.h"

#include <fstream>

class FileOutputInterface : public OutputInterface
{
private:
	FILE* file;
public:
	FileOutputInterface(const char* filename);
	~FileOutputInterface();

	void write(short* buffer, int bufSize);
};

