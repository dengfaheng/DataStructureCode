#pragma once

template<typename T>
class Queue
{
public:
	virtual ~Queue() {}
	virtual bool empty() const = 0;

	virtual int size() const = 0;

	virtual T &front() = 0;

	virtual T& back() = 0;

	virtual void dequeue() = 0;

	virtual void enqueue(const T& theElement) = 0;
};

class queueEmpty
{
public:
	queueEmpty() {}
	~queueEmpty() {}
protected:
private:
};