// 15_ջӦ��_���ߵȼ���.cpp: �������̨Ӧ�ó������ڵ㡣
//
#include "../09_ջ_��������/arrayStack.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
	int n, r;//n��Ԫ�أ�r�Թ�ϵ
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
	//������ϵ
	arrayStack<int> *list = new arrayStack<int>[n + 1];
	int a, b;
	for (int i = 1; i <= r; i++)
	{
		cout << "Enter next relation/pair" << endl;
		cin >> a >> b;
		list[a].push(b);
		list[b].push(a);
	}
	//��ʼ��������ȼ���
	arrayStack<int> unprocessedList;
	bool * out = new bool[n + 1];
	for (int i = 1; i <= n; i++)
	{
		out[i] = false;
	}

	//����ȼ���
	for (int i = 1; i <= r; i++)
	{
		if (!out[i])
		{
			//����һ������
			cout << "Next class is: " << i << " ";
			out[i] = true;
			unprocessedList.push(i);
			//��unprocessdList��ȡ���������ʣ��Ԫ��
			while (!unprocessedList.empty())
			{
				int j = unprocessedList.top();
				unprocessedList.pop();
				//��list[j]�е�Ԫ������ͬһ��
				while (!list[j].empty())
				{
					int q = list[j].top();
					list[j].pop();
					if (!out[q])//δ�����
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

