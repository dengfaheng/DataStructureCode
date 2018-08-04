#pragma once

#include<iostream>

using std::ostream;

/************************************************************************/
/*�����ƣ�linearList		         										*/
/*�๦�ܣ����Ա�-���������ĳ�����											*/
/*�汾��	 1.0															*/
/*author:NULL															*/
/************************************************************************/
template <typename T>
class linearList
{
public:
	virtual ~linearList() {};
	virtual bool empty() const = 0;  //Ϊ��ʱ����  true
	virtual int size() const = 0;    //�������Ա��Ԫ�ظ���
	virtual T & get(int theIndex) const = 0;  //����������ȡԪ��
	virtual int indexOf(const T & theElement) const = 0; //��ȡԪ�ص�һ�γ��ֵ�����
	virtual void erase(int theIndex) = 0;   //ɾ������ΪtheIndex��Ԫ��
	virtual void insert(int theIndex, const T & theElement) = 0; //������������Ԫ��
	virtual void output(ostream & out) const = 0; //���������������Ա�

};