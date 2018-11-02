#include <iostream>

#include "linkedQueue.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
	linkedQueue<char> myQ;

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

	cout << "队列大小: " << myQ.size() << endl;

	cin.get();
	cin.get();
	return 0;
}