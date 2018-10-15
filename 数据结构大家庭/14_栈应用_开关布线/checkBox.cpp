#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include "../09_栈_数组描述/arrayStack.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

bool checkBox(int net[], int n)
{
	arrayStack<int> * s = new arrayStack<int>(n);
	for (int i = 0; i < n; i++)
	{
		if (!s->empty())
		{
			//可以布线
			if (net[i] == net[s->top()])
			{
				s->pop();
			}
			else
				s->push(i);
		}
		else
			s->push(i);
	}
	if (s->empty())
	{
		cout << "Switch box is routable" << endl;
		return true;
	}

	cout << "Switch box is not routable" << endl;
	return false;
}

int main()
{
	int net[] = { 1, 2, 3, 1, 2, 3, 4, 4 };
	checkBox(net, 8);

	cin.get();
	return 0;
}