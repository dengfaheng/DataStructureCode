#pragma once
#include "../02_线性表_数组描述/linearList.h"

template<typename T>
struct chainNode
{
	T element;
	chainNode<T> * next;

	chainNode(){}
	chainNode(const T & theElement) { this->element = theElement; }
	chainNode(const T & theElement, chainNode<T> * theNext) { this->element = theElement; this->next = theNext; }
};

template<typename T>
class chain : public linearList<T>
{
public:

	chain(int initialCapacity = 10);
	chain(const chain<T> &);
	~chain();

	//ADT方法
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T & get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream & out) const;
	void reverse();
	void insertFromHead(const T & theElement) { insert(0, theElement); }
	void insertFromBack(const T & theElement) { insert(listSize, theElement); }

protected:
	void checkIndex(int theIndex) const;
	chainNode<T> * firstNode; //point to the first node of chain
	int listSize;
	
};

