#pragma once

class OutputInterface
{
public:
	virtual void write(short* buffer, int bufSize) = 0;
};