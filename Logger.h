#pragma once

#include <string>

class Logger
{
public:
	enum Level
	{
		INFO,
		WARN,
		ERROR,
		CRITICAL
	};

	static void log(Level level, char* message);
	static void log(Level level, const char* message);
};

