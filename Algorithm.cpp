#include "Algorithm.h"
#include "Logger.h"
#include "SerialBlock.h"
#include "SineOscillator.h"

#include <vector>
#include <queue>

void Algorithm::process(float* buffer, unsigned int bufSize)
{
	this->algorithmBlock->process(buffer, bufSize);
}

void Algorithm::create(std::string structure)
{
	std::vector<Block*> blocks;

	blocks.push_back(new SineOscillator(400.f, 200.f, 1.f));
	blocks.push_back(new SineOscillator(100.f, 50.f, 1.f));
	blocks.push_back(new SineOscillator(50.f, 0.f, 1.f));
	blocks.push_back(new SineOscillator(200.f, 0.f, 1.f));

	int charsRead = 0;
	Block* block = nullptr;
	block = create_rec(structure, &blocks, &charsRead);
	this->algorithmBlock = block;
}

Block* Algorithm::create_rec(std::string substructure, std::vector<Block*>* blocks, int* charsRead)
{
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
}
