#pragma once
#include "../17_队列_抽象类/Queue.h"

template<typename T>
struct chainNode
{
	T element;
	chainNode<T> * next;

	chainNode() {}
	chainNode(const T & theElement) { this->element = theElement; }
	chainNode(const T & theElement, chainNode<T> * theNext) { this->element = theElement; this->next = theNext; }
};

template<typename T>
class linkedQueue :public Queue<T>
{
public:
	linkedQueue(int initialCapacity = 5);
	~linkedQueue();
	bool empty() const { return (queueFront == NULL); }
	int size() const { return queueSize; }
	T &front();
	T& back();
	void dequeue();
	void enqueue(const T& theElement);

protected:
	chainNode<T> * queueFront;
	chainNode<T> * queueBack;
	int queueSize;
};

template<typename T>
linkedQueue<T>::linkedQueue(int initialCapacity)
{
	queueFront = queueBack = NULL;
	queueSize = 0;
}

template<typename T>
linkedQueue<T>::~linkedQueue()
{
	while (queueFront != NULL)
	{
		chainNode<T> * nextNode = queueFront->next;
		delete queueFront;
		queueFront = nextNode;
	}
}


template<typename T>
T& linkedQueue<T>::front()
{
	if (empty())
	{
		throw queueEmpty();
	}
	return queueFront->element;
}

template<typename T>
T& linkedQueue<T>::back()
{
	if (empty())
	{
		throw queueEmpty();
	}
	return queueFront->element;
}

template<typename T>
void linkedQueue<T>::dequeue()
{
	if (empty())
	{
		throw queueEmpty();
	}
	chainNode<T> *nextNode = queueFront->next;
	delete queueFront;
	queueFront = nextNode;
	queueSize--;
}

template<typename T>
void linkedQueue<T>::enqueue(const T& theElement)
{
	chainNode<T> *newNode = new chainNode<T>(theElement, NULL);
	if (empty())
	{
		queueFront = newNode;
	}
	else
	{
		queueBack->next = newNode;
	}
	queueBack = newNode;
	queueSize++;
}