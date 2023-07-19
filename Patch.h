#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>

class Patch
{
private:
	std::map<std::string, std::string> params;

	struct OperatorData
	{
		std::map<std::string, std::string> params;
	};
	std::vector<OperatorData*> operators;

	std::string algorithm;
public:
	void setAlgorithm(std::string algorithm) { this->algorithm = algorithm; };
	std::string getAlgorithm() { return this->algorithm; };

	void addPatchParameter(std::string paramName, std::string val)
	{
		params.insert(std::pair<std::string, std::string>(paramName, val));
	}

	std::string getPatchParameter(std::string paramName)
	{
		return params.at(paramName);
	}

	void addOperator()
	{
		operators.insert(operators.end(), new OperatorData);
	}

	void addOperatorParameter(int operatorId, std::string paramName, std::string val)
	{
		if (operatorId < operators.size())
		{
			operators.at(operatorId)->params.insert(std::pair<std::string, std::string>(paramName, val));
		}
	}

	std::string getOperatorParameter(int operatorId, std::string paramName)
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
			printf("%s = %s\n", it->first.c_str(), (it->second).c_str());
		}

		for (auto it = operators.begin(); it != operators.end(); it++)
		{
			for (auto it2 = (*it)->params.begin(); it2 != (*it)->params.end(); it2++)
			{
				printf("%s = %s\n", it2->first.c_str(), (it2->second).c_str());
			}
		}
	}
};

