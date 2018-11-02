#pragma once

#include "../17_队列_抽象类/Queue.h"
#include <algorithm>

using std::copy;

template<typename T>
class arrayQueue :public Queue<T>
{
public:
	arrayQueue(int initialCapacity = 5);
	~arrayQueue() { delete[] elements; }
	bool empty() const { return (queueBack == queueFront); }
	int size() const { return ((queueBack + arrayLength - queueFront) % arrayLength); }
	T &front();
	T& back();
	void dequeue();
	void enqueue(const T& theElement);

protected:
	T * elements;
	int queueFront;
	int queueBack;
	int arrayLength;
};

template<typename T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{
	arrayLength = initialCapacity;
	queueFront = 0;
	queueBack = 0;
	elements = new T[arrayLength];
}

template<typename T>
T &arrayQueue<T>::front()
{
	if (empty())
	{
		throw queueEmpty();
	}
	return elements[(queueFront + 1) % arrayLength];
}

template<typename T>
T &arrayQueue<T>::back()
{
	if (empty())
	{
		throw queueEmpty();
	}
	return elements[queueBack];
}

template<typename T>
void arrayQueue<T>::dequeue()
{
	if (empty())
	{
		throw queueEmpty();
	}
	queueFront = (queueFront + 1) % arrayLength;
	elements[queueFront].~T();
}

template<typename T>
void arrayQueue<T>::enqueue(const T& theElement)
{
	//自动增长
	if ((queueBack + 1) % arrayLength == queueFront)
	{
		//to do
		T * newQueue = new T[2 * arrayLength];

		int start = (queueFront + 1) % arrayLength;
		if (start < 2) //没有形成环
		{
			copy(elements + start, elements + arrayLength, newQueue);
		}
		else
		{
			copy(elements + start, elements + arrayLength, newQueue);
			copy(elements, elements + queueBack + 1, newQueue + arrayLength - start);
		}

		queueFront = arrayLength * 2 - 1;
		queueBack = arrayLength - 2; //队列长度arrayLength - 1
		arrayLength *= 2;
		delete[] elements;
		elements = newQueue;

	}
	queueBack = (queueBack + 1) % arrayLength;
	elements[queueBack] = theElement;
}