#include <iostream>
#include "illegalParameterValue.h"

using namespace std;

int abc(int a, int b, int c)
{
	if (a <= 0 || b <= 0 || c <= 0 )
	{
		throw illegalParameterValue("����a, b, c Ӧ�� > 0");
	}
	return a + b + c;
}

int main()
{
	try
	{
		cout << abc(2, 0, 4) << endl;
	}
	catch (illegalParameterValue e)
	{
		e.outPutMessage();
	}

	cin.get();

	return 0;
}