#include "arrayList.h"
#include "../01_�����쳣��/illegalParameterValue.h"
#include <iostream>
#include <algorithm>

using std::ostream;


template<typename T>
arrayList<T>::arrayList(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		char * smsg =  "Initial Capacity =  Must be > 0";
		throw illegalParameterValue(smsg);
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

template<typename T>
arrayList<T>::arrayList(const arrayList<T>  & theList)
{
	//��������
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	copy(theList.element, theList.element + listSize, element);
}

template<typename T>
void arrayList<T>::checkIndex(int theIndex) const
{
	//������0 ~ listSize - 1 ֮��
	if (theIndex < 0 || theIndex >= listSize)
	{
		char * msg = "Index over size";
		throw illegalParameterValue(msg);
	}
}

template<typename T>
T & arrayList<T>::get(int theIndex) const
{
	//��������ΪtheIndex��Ԫ�أ��������ڣ��׳��쳣
	checkIndex(theIndex);
	return element[theIndex];
}

template<typename T>
int arrayList<T>::indexOf(const T & theElement) const
{
	int theIndex = (int)(find(element, element + listSize, theElement) - element);
	if (theIndex == listSize)
	{
		return -1; //not found
	}
	else
		return theIndex;
}

template<typename T>
void arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	copy(element + theIndex + 1, element + listSize, element + theIndex);

	element[--listSize].~T();

	if (listSize < arrayLength / 4)
	{
		changeLength1D(element, listSize, listSize / 2);
		listSize /= 2;
	}

}

template<typename T>
void arrayList<T>::changeLength1D(T * theElement, int oldSize, int newSize)
{
	int theSize = std::min(oldSize, newSize);
	T * newElememt = new T[newSize];
	copy(theElement, theElement + theSize, newElememt);
	delete[] theElement;
	theElement = newElememt;
}

template<typename T>
void arrayList<T>::insert(int theIndex, const T & theElement)
{
	if ( theIndex < 0 || theIndex > listSize)
	{
		char * msg = "index over the range";
		throw illegalParameterValue(msg);
	}
	//full size
	if (listSize == arrayLength)
	{
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	element[theIndex] = theElement;
	listSize++;
}

template<typename T>
void arrayList<T>::output(ostream &out) const
{
	copy(element, element + listSize, ostream_iterator<T>(cout, "  "));
}

//����<<
template<typename T>
ostream & operator<<(ostream & out, const arrayList<T> &x)
{
	x.output(out); 
	return out;
}

