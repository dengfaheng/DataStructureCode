// 15_栈应用_离线等价类.cpp: 定义控制台应用程序的入口点。
//
#include "../09_栈_数组描述/arrayStack.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
	int n, r;//n个元素，r对关系
	cout << "Enter number of elements" << endl;
	cin >> n;
	if (n < 2)
	{
		cout << "Too few elements" << endl;
		return 1;
	}

	cout << "Enter number of relations" << endl;
	cin >> r;
	if (r < 1)
	{
		cout << "Too few relations" << endl;
		return 1;
	}
	//建立关系
	arrayStack<int> *list = new arrayStack<int>[n + 1];
	int a, b;
	for (int i = 1; i <= r; i++)
	{
		cout << "Enter next relation/pair" << endl;
		cin >> a >> b;
		list[a].push(b);
		list[b].push(a);
	}
	//初始化以输出等价类
	arrayStack<int> unprocessedList;
	bool * out = new bool[n + 1];
	for (int i = 1; i <= n; i++)
	{
		out[i] = false;
	}

	//输出等价类
	for (int i = 1; i <= r; i++)
	{
		if (!out[i])
		{
			//开启一个新类
			cout << "Next class is: " << i << " ";
			out[i] = true;
			unprocessedList.push(i);
			//从unprocessdList中取该类的其他剩余元素
			while (!unprocessedList.empty())
			{
				int j = unprocessedList.top();
				unprocessedList.pop();
				//表list[j]中的元素属于同一类
				while (!list[j].empty())
				{
					int q = list[j].top();
					list[j].pop();
					if (!out[q])//未输出的
					{
						cout << q << " ";
						out[q] = true;
						unprocessedList.push(q);
					}
				}
			}
			cout << endl;
		}

	}

	cout << "End of list of equivalence classes" << endl;

	cin.get();
	cin.get();
	cin.get();

	return 0;
}

