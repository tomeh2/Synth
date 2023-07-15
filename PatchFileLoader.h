#pragma once

#include "Patch.h"

#include <string>
#include <fstream>
#include <vector>

class PatchFileLoader
{
private:
	static std::vector<std::string> validTokens;

	static void initialize();
	static void tokenizeFile(FILE* file, std::vector<std::string>* tokens);
public:
	static Patch* loadPatchFile(std::string fileLocation);
};

