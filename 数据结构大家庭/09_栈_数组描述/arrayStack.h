#pragma once

#include <stack>
#include <algorithm>
#include "../01_参数异常类/illegalParameterValue.h"
#include "stackEmpty.h"
using std::stack;

template<typename T>
class arrayStack :public stack<T>
{
public:
	arrayStack(int initialCapacity = 10);
	~arrayStack() { delete[]stack; }
	void changeLength1D(T * theElement, int oldSize, int newSize);
	bool empty() const { return stackTop == -1; }
	int size() const { return stackTop + 1; }
	T & top()
	{
		if (stackTop == -1)
			throw stackEmpty();
		return stack[stackTop];
	}
	void pop();
	void push(const T & theElement);

private:
	int stackTop;
	int arrayLength;
	T * stack;

};

inline int myMin(int a, int b){ return (a<b ? a : b); }

template<typename T>
void arrayStack<T>::changeLength1D(T * theElement, int oldSize, int newSize)
{
	int theSize = myMin(oldSize, newSize);
	T * newElememt = new T[newSize];
	std::copy(theElement, theElement + theSize, newElememt);
	delete[] theElement;
	theElement = newElememt;
}

template<typename T>
arrayStack<T>::arrayStack(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		const char * smsg = "Initial Capacity =  Must be > 0";
		throw illegalParameterValue(smsg);
	}
	arrayLength = initialCapacity;
	stack = new T[arrayLength];
	stackTop = -1;
}

template<typename T>
void arrayStack<T>::push(const T & theElement)
{
	if (stackTop == arrayLength - 1)
	{
		changeLength1D(stack, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	stack[++stackTop] = theElement;
}


template<typename T>
void arrayStack<T>::pop()
{
	if (stackTop == -1)
	{
		throw stackEmpty();
	}
	if (((stackTop + 1) < arrayLength / 4) && (arrayLength > 10))
	{
		changeLength1D(stack, arrayLength, arrayLength / 2);
		arrayLength /= 2;
	}
	stack[stackTop--].~T();
}

