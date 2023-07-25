#include "Algorithm.h"
#include "Logger.h"
#include "SerialBlock.h"
#include "ParallelBlock.h"
#include "SineOscillator.h"
#include "Tokenizer.h"

#include <vector>
#include <queue>
#include <stack>

void Algorithm::process(float* buffer, unsigned int bufSize)
{
	this->algorithmBlock->process(buffer, bufSize);
}

void Algorithm::createOperators(Patch* patch, std::vector<Block*>* blocks)
{
	for (int i = 0; i < patch->getOperatorCount(); i++)
	{
		SineOscillator* osc = new SineOscillator(atof(patch->getOperatorParameter(i, "f").c_str()),
			atof(patch->getOperatorParameter(i, "mindex").c_str()),
			atof(patch->getOperatorParameter(i, "a").c_str()));

		this->operators.insert(this->operators.end(), osc);

		blocks->insert(blocks->end(), osc);

		std::string envName = patch->getOperatorParameter(i, "envelope");
		if (envName.compare("") != 0)
		{

		}
	}
}

void Algorithm::create(Patch* patch)
{
	std::vector<Block*> blocks;

	createOperators(patch, &blocks);

	int charsRead = 0;
	Block* block = nullptr;

	std::vector<Token*> tokens;
	Tokenizer t(patch->getPatchParameter("algorithm"));
	t.addSeparatorChar('(');
	t.addSeparatorChar(')');
	t.addSeparatorChar(',');
	t.tokenize(&tokens);

	int tokenIndex = 0;
	block = create_rec(&tokens, &tokenIndex);
	this->algorithmBlock = block;
}

void Algorithm::setBaseFrequency(float freq)
{
	for (auto it = this->operators.begin(); it != this->operators.end(); it++)
	{
		(*it)->setBaseFreq(freq);
	}
}


// NEEDS REWORK
Block* Algorithm::create_rec(std::vector<Token*>* tokens, int* tokenIndex)
{
	char msg[256];

	Block* b = nullptr;
	if (tokens->at(*tokenIndex)->getData().compare("s") == 0)
		b = new SerialBlock();
	else if (tokens->at(*tokenIndex)->getData().compare("p") == 0)
		b = new ParallelBlock();
	else
	{
		sprintf(msg, "Unrecognized algorithm construct %s", tokens->at(*tokenIndex)->getData().c_str());
		Logger::log(Logger::ERROR, msg);
		delete b;
		return nullptr;
	}
	(*tokenIndex)++;

	if (tokens->at(*tokenIndex)->getData().compare("(") != 0)
	{
		sprintf(msg, "Expected ( but got %s", tokens->at(*tokenIndex)->getData().c_str());
		Logger::log(Logger::ERROR, msg);
		delete b;
		return nullptr;
	}
	(*tokenIndex)++;

	do
	{
		if (tokens->at(*tokenIndex)->getData().compare("p") == 0 || tokens->at(*tokenIndex)->getData().compare("s") == 0)
		{
			Block* bRet = create_rec(tokens, tokenIndex);

			if (bRet == nullptr)
				return nullptr;

			b->insert(bRet);
		}
		else
		{
			size_t operatorNum = atoi(tokens->at(*tokenIndex)->getData().c_str());
			b->insert(this->operators.at(operatorNum - 1));
			(*tokenIndex)++;
		}

		if (tokens->at(*tokenIndex)->getData().compare(",") == 0)
			(*tokenIndex)++;
		else if (tokens->at(*tokenIndex)->getData().compare(")") == 0)
			;
		else
		{
			sprintf(msg, "Invalid token encountered while building algorithm %s", tokens->at(*tokenIndex)->getData().c_str());
			Logger::log(Logger::ERROR, msg);
			delete b;
			return nullptr;
		}
	} while (tokens->at(*tokenIndex)->getData().compare(")") != 0);
	(*tokenIndex)++;

	return b;
}
