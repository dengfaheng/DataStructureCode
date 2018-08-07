#pragma once

#include "../01_参数异常类/illegalParameterValue.h"
#include "../03_线性表_链式描述/chain.h"
#include "../03_线性表_链式描述/chain.cpp"
#include "../09_栈_数组描述/stackEmpty.h"
#include <stack>
#include <algorithm>
using std::stack;

template<typename T>
class linkedStack : public stack<T>
{
public:
	linkedStack(int initialCapacity = 10) { stackTop = NULL; stackSize = 0; }
	~linkedStack();
	bool empty() const { return stackSize == 0; }
	int size() const { return stackSize; }
	T & top()
	{
		if (stackSize == 0)
		{
			throw stackEmpty();
		}
		return stackTop->element;
	}
	void pop();
	void push(const T & theElement)
	{
		stackTop = new chainNode<T>(theElement, stackTop);
	}

private:
	chainNode<T> * stackTop;
	int stackSize;
};

template<typename T>
linkedStack::~linkedStack()
{
	while (stackTop != NULL)
	{
		chainNode<T> *nextNode = stackTop->next;
		delete stackTop;
		stackTop = nextNode;
	}
}

template<typename T>
void linkedStack::pop()
{
	if (stackSize == 0)
	{
		throw stackEmpty();
	}
	chainNode<T> * nextNode = stackTop->next;
	delete stackTop;
	stackTop = nextNode;
	stackSize--;
}

