#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include "../01_�����쳣��/illegalParameterValue.h"

using std::cin;
using std::cout;
using std::endl;

//������ƶ���x,yλ��
void gotoxy(COORD c)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//�ж������Ƿ���
bool isOneLine(COORD a, COORD b, COORD c)
{
	if ( (c.Y - a.Y) * (b.X - a.X) == (b.Y - a.Y) * (c.X - a.X) )
	{
		return true;
	}
	return false;
}

//��������ɵ��������ڲ���ȡһ��
COORD pointOfTriangle(COORD a, COORD b, COORD c)
{
	COORD point = { 0, 0 };
	if (!isOneLine(a, b, c))
	{
		throw illegalParameterValue("Parameters error, three points on one line");
	}

	return point;
}

int main()
{
	system("mode con cols=100 lines=30");
	srand((unsigned int)time(0));
	COORD coord;

	for (int i = 0; i < 12; i++)
	{
		char ch = i + 'A';
		coord.X = rand() % 30 + 30;
		coord.Y = rand() % 10 + 10;
		gotoxy(coord);
		cout << ch;
	}


	cin.get();
	return 0;
}