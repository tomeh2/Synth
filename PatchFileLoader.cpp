#include "PatchFileLoader.h"
#include "Logger.h"
#include "Tokenizer.h"

void PatchFileLoader::tokenizeFile(FILE* file, std::vector<std::string>* tokens)
{
	while (!feof(file))
	{
		
	}
}

Patch* PatchFileLoader::loadPatchFile(std::string fileLocation)
{
	FILE* file;
	file = fopen(fileLocation.c_str(), "r");

	if (file == nullptr)
	{
		Logger::log(Logger::ERROR, ("Could not open file " + fileLocation).c_str());
		return nullptr;
	}
	Logger::log(Logger::INFO, ("Opened patch file " + fileLocation).c_str());

	std::vector<std::string> tokens;
	Tokenizer t;
	t.tokenizeFile(file, &tokens);

	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++)
	{
		printf("%s\n", it->c_str());
	}

	return nullptr;
}
