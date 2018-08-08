#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include "../09_ջ_��������/arrayStack.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

arrayStack<int> tower[4];

//����z������x���ϵ�n�������ƶ���y��
void moveAndShow(int n, int x, int y, int z)
{
	if (n > 0)
	{
		moveAndShow(n - 1, x, z, y);
		int d = tower[x].top();
		tower[x].pop();
		tower[y].push(d);
		cout << "Move disk " << d << " from tower "
			<< x << " to top of tower " << y << endl;
		moveAndShow(n - 1, z, y, x);
	}
}

void towersOfHanoi(int n)
{
	//��ʼ״̬
	for (int i = n; i > 0; i--)
	{
		tower[1].push(i);
	}

	moveAndShow(n, 1, 2, 3);
}

int main()
{
	int n;
	cin >> n;
	cout << "��ŵ���ƶ�������£�" << endl;
	towersOfHanoi(n);

	cin.get();
	cin.get();
	return 0;
}