#pragma once

#include<iostream>

using std::ostream;

/************************************************************************/
/*类名称：linearList		         										*/
/*类功能：线性表-数组描述的抽象类											*/
/*版本：	 1.0															*/
/*author:NULL															*/
/************************************************************************/
template <typename T>
class linearList
{
public:
	virtual ~linearList() {};
	virtual bool empty() const = 0;  //为空时返回  true
	virtual int size() const = 0;    //返回线性表的元素个数
	virtual T & get(int theIndex) const = 0;  //根据索引获取元素
	virtual int indexOf(const T & theElement) const = 0; //获取元素第一次出现的索引
	virtual void erase(int theIndex) = 0;   //删除索引为theIndex的元素
	virtual void insert(int theIndex, const T & theElement) = 0; //根据索引插入元素
	virtual void output(ostream & out) const = 0; //利用输出流输出线性表

};