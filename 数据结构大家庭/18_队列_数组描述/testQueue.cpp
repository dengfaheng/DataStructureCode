#include <iostream>

#include "arrayQueue.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
	arrayQueue<char> myQ;

	if (myQ.empty())
	{
		cout << "队列为空" << endl;
	}

	myQ.enqueue('A');
	myQ.enqueue('B');
	myQ.enqueue('C');
	myQ.enqueue('D');
	myQ.enqueue('E');
	myQ.enqueue('E');
	myQ.enqueue('E');
	myQ.enqueue('E');
	myQ.enqueue('E');

	cout << "队列大小: " << myQ.size() << endl;

	while (!myQ.empty())
	{
		cout << myQ.front() << endl;
		myQ.dequeue();
	}

	cin.get();
	cin.get();
	return 0;
}