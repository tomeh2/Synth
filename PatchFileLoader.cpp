#include "PatchFileLoader.h"
#include "Logger.h"
#include "Tokenizer.h"
#include "Parser.h"

void PatchFileLoader::tokenizeFile(FILE* file, std::vector<std::string>* tokens)
{
	while (!feof(file))
	{
		
	}
}

int PatchFileLoader::loadPatchFile(std::string fileLocation, std::map<std::string, Patch*>* patchMap)
{
	FILE* file;
	file = fopen(fileLocation.c_str(), "r");

	if (file == nullptr)
	{
		Logger::log(Logger::ERROR, ("Could not open file " + fileLocation).c_str());
		return -1;
	}
	Logger::log(Logger::INFO, ("Opened patch file " + fileLocation).c_str());

	std::vector<Token*> tokens;
	Tokenizer t(file);
	t.addNeutralChar('_');
	t.addNeutralChar('(');
	t.addNeutralChar(')');
	t.addNeutralChar(',');

	t.addSeparatorChar('{');
	t.addSeparatorChar('}');
	t.addSeparatorChar(';');
	t.addSeparatorChar('=');
	t.tokenize(&tokens);

	Parser::parse(&tokens, patchMap);

	return 0;
}
