#pragma once

#include <vector>
#include <string>

class Patch
{
private:
	std::vector<float> operatorFrequencies;
	std::vector<float> operatorModIndexes;
	std::vector<float> operatorAmplitudes;
	std::string algorithm;
public:
	void setAlgorithm(std::string algorithm) { this->algorithm = algorithm; };
	std::string getAlgorithm() { return this->algorithm; };

	void addOperator(float operatorFreq, float operatorModIndex, float operatorAmp)
	{
		this->operatorFrequencies.push_back(operatorFreq);
		this->operatorModIndexes.push_back(operatorModIndex);
		this->operatorAmplitudes.push_back(operatorAmp);
	}

	float getOperatorFreq(int operatorNum) { return this->operatorFrequencies.at(operatorNum); }
	float getOperatorModIndex(int operatorNum) { return this->operatorModIndexes.at(operatorNum); }
	float getOperatorAmp(int operatorNum) { return this->operatorAmplitudes.at(operatorNum); }
};

