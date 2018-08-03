#pragma once

#include "linearList.h"
#include<iostream>

using std::ostream;

template<typename T>
class arrayList : public linearList<T>
{
public:
	arrayList(int initialCapacity = 10); //����
	arrayList(const arrayList<T> &);   //��������
	~arrayList() { delete[] element; } //����

	//ADT����
	bool empty() const { return listSize = 0; }
	int size() const { return listSize; }
	T & get(int theIndex) const;
	int indexOf(const T & theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T & theElement);
	void output(ostream & out) const;

	//��������
	int capacity() const { return arrayLength; }

protected:
	void checkIndex(int theIndex) const; //�ж������Ƿ���Ч����Ч���׳��쳣
	void changeLength1D(T * theElement, int oldSize, int newSize);
	T * element;
	int arrayLength;
	int listSize;
};

