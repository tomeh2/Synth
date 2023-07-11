#include "Logger.h"

#include <stdio.h>

void Logger::log(Logger::Level level, std::string message)
{
	std::string levelStr;

	switch (level)
	{
	case Logger::INFO:
		levelStr = "INFO";
		break;
	case Logger::WARN:
		levelStr = "WARN";
		break;
	case Logger::ERROR:
		levelStr = "ERROR";
		break;
	case Logger::CRITICAL:
		levelStr = "CRITICAL";
		break;
	default:
		break;
	}

	printf("[%s]: %s", levelStr, message);
}