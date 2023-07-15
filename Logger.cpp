#include "Logger.h"

#include <stdio.h>

void Logger::log(Logger::Level level, char* message)
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

	printf("[%s]: %s\n", levelStr.c_str(), message);
}

void Logger::log(Logger::Level level, const char* message)
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

	printf("[%s]: %s\n", levelStr.c_str(), message);
}