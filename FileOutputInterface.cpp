#include "FileOutputInterface.h"

#include "Logger.h"

FileOutputInterface::FileOutputInterface(const char* filename)
{
	if ((file = fopen(filename, "wb")) == nullptr)
	{
		char msg[256];
		sprintf(msg, "Failed to open output file %s", filename);
		Logger::log(Logger::ERROR, msg);
		return;
	}
}

FileOutputInterface::~FileOutputInterface()
{
	fclose(file);
}

void FileOutputInterface::write(short* buffer, int bufSize)
{
	fwrite(buffer, sizeof(short), bufSize, file);
}
