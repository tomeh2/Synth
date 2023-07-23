#include "Algorithm.h"
#include "Logger.h"
#include "SerialBlock.h"
#include "ParallelBlock.h"
#include "SineOscillator.h"
#include "Tokenizer.h"

#include <vector>
#include <queue>

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
	}
}

void Algorithm::create(Patch* patch)
{
	std::vector<Block*> blocks;

	createOperators(patch, &blocks);

	int charsRead = 0;
	Block* block = nullptr;

	block = create_rec(patch->getPatchParameter("algorithm"), &blocks, &charsRead);
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
Block* Algorithm::create_rec(std::string substructure, std::vector<Block*>* blocks, int* charsRead)
{
	//Tokenizer t;


	int state = 0;
	int currOperatorNum = 0;
	std::vector<int> operators;
	std::queue<Block*> generatedBlocks;

	for (unsigned int i = 1; i < substructure.size(); i++)
	{
		//CHECK STARTING CHARACTER
		if (state == 0)
		{
			if (substructure[i] != '(')
			{
				Logger::log(Logger::Level::ERROR, "Algorithm creation syntax error. Expected \'(\' but got " + substructure[i]);
				*charsRead = -1;
				return nullptr;
			}
			else
			{
				state = 1;
			}
			
		}

		if (state == 1)
		{
			if (isdigit(substructure[i]))
			{
				state = 2;
				i--;
				continue;
			}
		}

		//NUMBER PARSING
		if (state == 2)
		{
			if (isdigit(substructure[i]))
			{
				currOperatorNum *= 10;
				currOperatorNum += substructure[i] - 48;
			}
			else if (isalpha(substructure[i]))
			{
				Block* tmp = nullptr;
				int skip;
				tmp = create_rec(substructure.substr(i, substructure.size() - i), blocks, &skip);
				generatedBlocks.push(tmp);
				operators.push_back(-1);
				i += skip;
			}
			else if (substructure[i] == ')')
			{
				*charsRead = i + 1;
				operators.push_back(currOperatorNum);
				break;
			}
			else if (substructure[i] == ',')
			{
				operators.push_back(currOperatorNum);
				currOperatorNum = 0;
			}
			else
			{
				Logger::log(Logger::Level::ERROR, "Algorithm creation syntax error.");
			}
		}
	}

	if (substructure[0] == 'c')
	{
		SerialBlock* ser = new SerialBlock;
		for (std::vector<int>::iterator it = operators.begin(); it != operators.end(); it++)
		{
			if (*it == -1)
			{
				ser->insert(generatedBlocks.front());
				generatedBlocks.pop();
				it--;
			}
			else
				ser->insert(blocks->at((*it) - 1));
		}
		return ser;
	} 
	else if (substructure[0] == 'p')
	{
		ParallelBlock* ser = new ParallelBlock;
		for (std::vector<int>::iterator it = operators.begin(); it != operators.end(); it++)
		{
			if (*it == -1)
			{
				ser->insert(generatedBlocks.front());
				generatedBlocks.pop();
				it--;
			}
			else
				ser->insert(blocks->at((*it) - 1));
		}
		return ser;
	}
}
