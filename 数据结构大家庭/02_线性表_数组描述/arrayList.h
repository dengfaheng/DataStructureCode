#pragma once

#include "linearList.h"
#include<iostream>

using std::ostream;

template<typename T>
class arrayList : public linearList<T>
{
public:
	arrayList(int initialCapacity = 10); //构造
	arrayList(const arrayList<T> &);   //拷贝构造
	~arrayList() { delete[] element; } //析构

	//ADT方法
	bool empty() const { return listSize = 0; }
	int size() const { return listSize; }
	T & get(int theIndex) const;
	int indexOf(const T & theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T & theElement);
	void output(ostream & out) const;

	//其他方法
	int capacity() const { return arrayLength; }

protected:
	void checkIndex(int theIndex) const; //判断索引是否有效，无效则抛出异常
	void changeLength1D(T * theElement, int oldSize, int newSize);
	T * element;
	int arrayLength;
	int listSize;
};

