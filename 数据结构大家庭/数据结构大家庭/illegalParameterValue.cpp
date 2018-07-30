#include "illegalParameterValue.h"

#include <iostream>

illegalParameterValue::illegalParameterValue()
{
}

illegalParameterValue::illegalParameterValue(const char * message):m_message(message)
{
}

void illegalParameterValue::outPutMessage()
{
	std::cout << m_message << std::endl;
}

illegalParameterValue::~illegalParameterValue()
{
}
