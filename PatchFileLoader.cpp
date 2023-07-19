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

	std::vector<Token*> tokens;
	Tokenizer t;
	t.tokenizeFile(file, &tokens);

#ifdef _DEBUG
	for (auto it = tokens.begin(); it != tokens.end(); it++)
	{
		if ((*it)->getType() == Token::NUMBER_INT)
			printf("Type: INT | Val: %s\n", (*it)->getData().c_str());
		else if ((*it)->getType() == Token::NUMBER_FLOAT)
			printf("Type: FLOAT | Val: %s\n", (*it)->getData().c_str());
		else if ((*it)->getType() == Token::STRING)
			printf("Type: STR | Val: %s\n", (*it)->getData().c_str());
		else if ((*it)->getType() == Token::CURLY_START)
			printf("Type: CURLY_START \n");
		else if ((*it)->getType() == Token::CURLY_END)
			printf("Type: CURLY_END \n");
		else if ((*it)->getType() == Token::EQUALS)
			printf("Type: EQUALS \n");
		else if ((*it)->getType() == Token::SEMICOLON)
			printf("Type: SEMICOLON \n");
	}
#endif
	std::map<std::string, Patch*> map;

	Parser::parse(&tokens, &map);
	map.at("123")->printInfo();

	return nullptr;
}
