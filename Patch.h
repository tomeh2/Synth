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

	struct EnvelopeSegment
	{
		std::map<std::string, std::string> params;
	};

	struct EnvelopeData
	{
		std::vector<EnvelopeSegment*> envSegments;
	};
	std::map<std::string, EnvelopeData*> envelopes;
public:
	~Patch()
	{
		for (int i = 0; i < operators.size(); i++)
		{
			delete operators.at(i);
		}

		for (auto it = envelopes.begin(); it != envelopes.end(); it++)
		{
			for (int i = 0; i < (*it).second->envSegments.size(); i++)
			{
				delete (*it).second->envSegments.at(i);
			}

			delete (*it).second;
		}
		envelopes.clear();
	}

	void addPatchParameter(std::string paramName, std::string val)
	{
		params.insert(std::pair<std::string, std::string>(paramName, val));
	}

	std::string getPatchParameter(std::string paramName)
	{
		if (params.find(paramName) == params.end())
			return "";
		else
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

	int getOperatorCount()
	{
		return operators.size();
	}

	std::string getOperatorParameter(int operatorId, std::string paramName)
	{
		if (operatorId < operators.size())
		{
			if (operators.at(operatorId)->params.find(paramName) == operators.at(operatorId)->params.end())
				return "";
			else
				return operators.at(operatorId)->params.at(paramName);
		}
	}

	void addEnvelope(std::string name)
	{
		envelopes.insert(std::pair<std::string, EnvelopeData*>(name, new EnvelopeData));
	}

	void addEnvelopeSegment(std::string name)
	{
		envelopes.at(name)->envSegments.insert(envelopes.at(name)->envSegments.end(), new EnvelopeSegment);
	}

	void addEnvelopeSegmentParam(std::string name, int segmentId, std::string paramName, std::string val)
	{
		envelopes.at(name)->envSegments.at(segmentId)->params.insert(std::pair<std::string, std::string>(paramName, val));
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

		for (auto it = envelopes.begin(); it != envelopes.end(); it++)
		{
			for (auto it2 = (*it).second->envSegments.begin(); it2 != (*it).second->envSegments.end(); it2++)
			{
				for (auto it3 = (*it2)->params.begin(); it3 != (*it2)->params.end(); it3++)
				{
					printf("%s = %s\n", (*it3).first.c_str(), (*it3).second.c_str());
				}
			}
		}
	}
};

