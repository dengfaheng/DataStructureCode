#pragma once

#include <string>
using std::string;

class illegalParameterValue
{
private:
	string m_message;
public:
	illegalParameterValue();
	illegalParameterValue(const char *message);

	void outPutMessage();

	~illegalParameterValue();
};

