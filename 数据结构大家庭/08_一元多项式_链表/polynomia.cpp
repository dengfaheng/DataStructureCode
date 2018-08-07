#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <algorithm>
#include <string>
#include "../03_线性表_链式描述/chain.h"
#include "../03_线性表_链式描述/chain.cpp"
#include "../01_参数异常类/illegalParameterValue.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::ostream;

struct MONOMIAL
{
	int power; //幂次
	int ratio;   //系数
	bool operator==(const MONOMIAL & t) { return ((power == t.power) && (ratio == t.ratio)); }
	bool operator!=(const MONOMIAL & t) { return ((power != t.power) && (ratio != t.ratio)); }

};

void chain<MONOMIAL>::output(ostream &out) const
{
	for (chainNode<MONOMIAL> * currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
	{
		out << currentNode->element.ratio << "X^" << currentNode->element.power;
		if (currentNode->next == NULL)
		{
			continue;
		}
		out << " + ";
	}
	out << endl;
}

inline int maxNum(int a, int b)
{
	return a > b ? a : b;
}

template<typename T>
class CPolynomial
{
public:
	chain<MONOMIAL> polyn;
	int maxPower;

public:
	CPolynomial(): maxPower(0)
	{
		polyn.clear();
	}
	//拷贝构造, 利用链表本身的拷贝构造函数
	CPolynomial(const CPolynomial & p): maxPower(p.maxPower), polyn(p.polyn) {}

	void input(istream & is)
	{
		cout << "请先输入最高次幂： ";
		is >> maxPower;
		if (maxPower < 0)
		{
			throw illegalParameterValue("Power must be > 0");
		}
		cout << "按降幂方式，依次输入各项系数(到0次幂系数为止，包含0次幂)： " << endl;
		for (int i = maxPower; i >= 0; i--)
		{
			MONOMIAL one;
			one.power = i;
			is >> one.ratio;
			polyn.insertFromHead(one);
		}
	}
	void output(ostream & out) const 
	{
		polyn.output(out);
	}
	//加上一个多项式
	void add(const CPolynomial & p)
	{
		int theMaxD = maxNum(maxPower, p.maxPower);
		for (int i = 0; i <= theMaxD; i++)
		{
			if (i > maxPower)
			{
				MONOMIAL one = p.polyn.get(i);
				polyn.insertFromBack(one);
				continue;
			}
			MONOMIAL one = polyn.get(i);
			polyn.erase(i);
			one.ratio += p.polyn.get(i).ratio;
			polyn.insert(i, one);
		}
	}
	//减去一个多项式
	void subtract(const CPolynomial & p)
	{
		int theMaxD = maxNum(maxPower, p.maxPower);
		for (int i = 0; i <= theMaxD; i++)
		{
			if (i > maxPower)
			{
				MONOMIAL one = p.polyn.get(i);
				one.ratio = 0 - one.ratio;
				polyn.insertFromBack(one);
				continue;
			}
			MONOMIAL one = polyn.get(i);
			polyn.erase(i);
			one.ratio -= p.polyn.get(i).ratio;
			polyn.insert(i, one);
		}
	}



};

int main()
{
	CPolynomial<int> p1, p2;
	p1.input(cin);
	p2.input(cin);

	p1.output(cout);
	p2.output(cout);

	p1.add(p2);
	p1.output(cout);

	p1.subtract(p2);
	p1.output(cout);


	system("pause");
	system("pause");

	return 0;
}