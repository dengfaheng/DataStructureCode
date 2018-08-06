#include "chain.h"
#include "../01_参数异常类/illegalParameterValue.h"
#include <iostream>
#include <iomanip>
using std::endl;
using std::ostream;

template<typename T>
chain<T>::chain(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		const char * smsg = "Initial Capacity =  Must be > 0";
		throw illegalParameterValue(smsg);
	}
	firstNode = NULL;
	listSize = 0;
}

template<typename T>
chain<T>::chain(const chain<T>  & theList)
{
	//拷贝构造
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
	//索引在0 ~ listSize - 1 之间
	if (theIndex < 0 || theIndex >= listSize)
	{
		const char * msg = "Index over range";
		throw illegalParameterValue(msg);
	}
}

template<typename T>
T & chain<T>::get(int theIndex) const
{
	//返回索引为theIndex的元素，若不存在，抛出异常
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
		const char * msg = "index over the range";
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
		out << std::setw(4) <<currentNode->element << "  ";
	}
	out << endl;
}

//链表反转
template<typename T>
void chain<T>::reverse()
{
	chainNode<T> *p1, *p2, *p3;
	p1 = p2 = p3 = NULL; //防止野指针
	p1 = firstNode;

	if (p1 != NULL)
	{
		p2 = p1->next;
		while (p2 != NULL)
		{
			p3 = p2->next;  //布局第三个点
			p2->next = p1;  //指针转向
			p1 = p2;        //循环移动
			p2 = p3;
		}
		firstNode->next = NULL;
		firstNode = p1;
	}
	
}

//重载<<
template<typename T>
ostream & operator<<(ostream & out, const chain<T> &x)
{
	x.output(out);
	return out;
}

