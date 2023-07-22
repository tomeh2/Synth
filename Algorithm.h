#pragma once

#include "Block.h"
#include "Patch.h"
#include "SineOscillator.h"

#include <string>
#include <vector>

class Algorithm : public Block
{
private:
	Block* algorithmBlock = nullptr;
	std::vector<SineOscillator*> operators;
	
	Block* create_rec(std::string substructure, std::vector<Block*>* blocks, int* block);
	void createOperators(Patch* patch, std::vector<Block*>* blocks);
public:
	void process(float* buffer, unsigned int bufSize);
	void create(Patch* patch);

	void setBaseFrequency(float freq);
};