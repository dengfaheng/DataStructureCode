#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include "../09_Õ»_Êı×éÃèÊö/arrayStack.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void printMatchPairs(string expr)
{
	arrayStack<int> s;
	int length = (int)expr.size();

	for (int i = 0; i< length; i++)
	{
		if (expr.at(i) == '(')
		{
			s.push(i);
		}
		else
		{
			if (expr.at(i) == ')')
			{
				try
				{
					cout << s.top() << " <--> " << i << endl;
					s.pop();
				}
				catch (stackEmpty)
				{
					cout << "No match for right parenthesis" << " at " << i << endl;
				}
			}
		}
	}

	while (!s.empty())
	{
		cout << "No match for left parenthesis at " << s.top() << endl;
		s.pop();
	}
}

int main()
{
	char buf[255];
	cin.getline(buf, 255);
	string inp(buf);

	printMatchPairs(inp);

	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();

	return 0;
}
