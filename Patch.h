#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>

class Patch
{
private:
	std::map<std::string, void*> params;

	struct OperatorData
	{
		std::map<std::string, void*> params;
	};
	std::vector<OperatorData*> operators;

	std::string algorithm;
public:
	void setAlgorithm(std::string algorithm) { this->algorithm = algorithm; };
	std::string getAlgorithm() { return this->algorithm; };

	void addPatchParameter(std::string paramName, void* val)
	{
		params.insert(std::pair<std::string, void*>(paramName, val));
	}

	void* getPatchParameter(std::string paramName)
	{
		return params.at(paramName);
	}

	void addOperator()
	{
		operators.insert(operators.end(), new OperatorData);
	}

	void addOperatorParameter(int operatorId, std::string paramName, void* val)
	{
		if (operatorId < operators.size())
		{
			operators.at(operatorId)->params.insert(std::pair<std::string, void*>(paramName, val));
		}
	}

	void* getOperatorParameter(int operatorId, std::string paramName)
	{
		if (operatorId < operators.size())
		{
			return operators.at(operatorId)->params.at(paramName);
		}
	}

	void printInfo()
	{
		printf("Patch Info\n");
		for (auto it = params.begin(); it != params.end(); it++)
		{
			printf("%s = %s\n", it->first.c_str(), ((std::string*)it->second)->c_str());
		}
	}
};

