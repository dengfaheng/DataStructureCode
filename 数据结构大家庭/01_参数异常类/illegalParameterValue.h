#pragma once

#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class illegalParameterValue
{
public:
	illegalParameterValue() : m_message("Illegal Parameter Values") {}
	illegalParameterValue(const char * message):m_message(message){}
	void outPutMessage() { cout << m_message << endl; }

private:
	string m_message;
};