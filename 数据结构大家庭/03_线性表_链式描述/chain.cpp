#include "chain.h"
#include <iostream>
using std::endl;
using std::ostream;

template<typename T>
chain<T>::chain(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		char * smsg = "Initial Capacity =  Must be > 0";
		throw illegalParameterValue(smsg);
	}
	firstNode = NULL;
	listSize = 0;
}

template<typename T>
chain<T>::chain(const chain<T>  & theList)
{
	//��������
	listSize = theList.listSize;
	if (listSize == 0)
	{
		firstNode = NULL;
		return;
	}
	chainNode<T> * sourceNode = theList.firstNode;
	firstNode = new chainNode<T>(sourceNode->element);
	sourceNode = sourceNode->next;
	chainNode<T> * targeNode = firstNode;

	while (sourceNode != NULL)
	{
		targeNode->next = new chainNode<T>(sourceNode->element);
		targeNode = targeNode->next;
		sourceNode = sourceNode->next;
	}

	targeNode->next = NULL;
}

template<typename T>
chain<T>::~chain()
{
	while (firstNode != NULL)
	{
		chainNode<T> * nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}


template<typename T>
void chain<T>::checkIndex(int theIndex) const
{
	//������0 ~ listSize - 1 ֮��
	if (theIndex < 0 || theIndex >= listSize)
	{
		char * msg = "Index over range";
		throw illegalParameterValue(msg);
	}
}

template<typename T>
T & chain<T>::get(int theIndex) const
{
	//��������ΪtheIndex��Ԫ�أ��������ڣ��׳��쳣
	checkIndex(theIndex);
	chainNode<T> * currentNode = firstNode;

	for (int i = 0; i < theIndex; i++)
	{
		currentNode = currentNode->next;
	}

	return  currentNode->element;

}

template<typename T>
int chain<T>::indexOf(const T & theElement) const
{
	chainNode<T> * currentNode = firstNode;
	int index = 0;
	while (currentNode != NULL && currentNode->element != theElement)
	{
		currentNode = currentNode->next;
		index++;
	}
	if (currentNode == NULL)
	{
		return -1;
	}
	else
	{
		return index;
	}
}



template<typename T>
void chain<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	chainNode<T> * deleteNode;
	if (theIndex == 0)
	{
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{
		chainNode<T> * p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}
		deleteNode = p->next;
		p->next = p->next->next;
	}
	listSize--;
	delete deleteNode;

}


template<typename T>
void chain<T>::insert(int theIndex, const T & theElement)
{
	if (theIndex < 0 || theIndex > listSize)
	{
		char * msg = "index over the range";
		throw illegalParameterValue(msg);
	}
	if (theIndex == 0)
	{
		firstNode = new chainNode<T>(theElement, firstNode);
	}
	else
	{
		chainNode<T> * p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}
		p->next = new chainNode<T>(theElement, p->next);
	}
	listSize++;
}


template<typename T>
void chain<T>::output(ostream &out) const
{
	for (chainNode<T> * currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
	{
		out << currentNode.element << "  ";
	}
	out << endl;
}

//����<<
template<typename T>
ostream & operator<<(ostream & out, const chain<T> &x)
{
	x.output(out);
	return out;
}

