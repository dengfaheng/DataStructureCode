#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <windows.h>
#include<stack>

using std::cout;
using std::cin;
using std::endl;
using std::stack;

typedef struct  
{
	int row;
	int col;
}POSITION;


const POSITION maze_size = { 20 , 60 };

int ** const maze = new int*[maze_size.row + 2];

stack<POSITION> path;
POSITION offset[4];//direction

void welcome();
void init();
void randomMaze();
bool findPath();
void outputMaze();
void setPathOnMaze();

int main()
{
	srand((unsigned int)time(NULL));
	welcome();
	init();
	randomMaze();

	cout << "Init Maze: " << endl;
	outputMaze();

	cout << endl << endl;

	if (findPath())
	{
		cout << "Find a path:" << endl;
		setPathOnMaze();
		outputMaze();
	}
	else
	{
		cout << "No path" << endl;
	}
		
	cin.get();
	cin.get();

	return 0;
}

void welcome()
{
	cout << "welcome to RAT IN MAZE" << endl;
	system("pause");
	system("cls");
}

void init()
{
	//偏移
	offset[0].row = 0; offset[0].col = 1; //right
	offset[1].row = 1; offset[1].col = 0; //down
	offset[2].row = 0; offset[2].col = -1; //left
	offset[3].row = -1; offset[3].col = 0; //up

	//maze = new int*[maze_size.row + 2];
	for (int i = 0; i < maze_size.row + 2; i++)
	{
		maze[i] = new int[maze_size.col + 2];
	}
}

//地图范围1 - maze_size 有围墙
void randomMaze()
{
	int i, j, rate;
	
	for (i = 0; i < maze_size.row + 2; i++)
	{
		for (j = 0; j < maze_size.col + 2; j++)
		{
			//设置围墙
			if ((i == 0) || (i == maze_size.row + 1) || (j == 0) || (j == maze_size.col + 1))
			{
				maze[i][j] = 1;
			}
			else
			{
				rate = rand() % 10+1;
				if (rate <= 3)
				{
					maze[i][j] = 1;//随机生成障碍
				}
				else
				{
					maze[i][j] = 0;
				}
			}
		}
	}
	//最后保证起点和终点能走
	maze[1][1] = maze[maze_size.row][maze_size.col] = 0;
}

void outputMaze()
{
	int i, j;
	for (i = 0; i < maze_size.row + 2; i++)
	{
		for (j = 0; j < maze_size.col + 2; j++)
		{
			if (maze[i][j] == 1)
			{
				cout << "*";
			}
			else if ((maze[i][j] == 0) || (maze[i][j] == 3))
			{
				cout << " ";
			}
			else
			{
				HANDLE hOut;
				hOut = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hOut,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "#";
				SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
		cout << endl;
	}
}

bool findPath()
{
	POSITION here; //当前位置
	here.row = here.col = 1;
	maze[1][1] = 3; //放置障碍，防止回来
	int option = 0; //next step
	const int lastOption = 3; 

	//find a path
	while ( here.row != maze_size.row || here.col != maze_size.col)
	{
		//not reach the end
		int r, c;
		while (option <= lastOption)
		{
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0)
			{
				break;
			}
			option++;//next choice
		}

		//相邻的位置能走？
		if (option <= lastOption)
		{
			path.push(here);
			here.row = r;
			here.col = c;
			maze[r][c] = 3; //走过了
			option = 0;
		}
		else
		{
			if (path.empty())
			{
				return false;
			}
			//go back
			maze[here.row][here.col] = 3; //此路不可通
			here = path.top();
			path.pop();
			option = 0;
		}
	}

	maze[maze_size.row][maze_size.col] = 2;

	return true;
}
void setPathOnMaze()
{
	POSITION pos;
	while (!path.empty())
	{
		pos = path.top();
		path.pop();
		maze[pos.row][pos.col] = 2;
	}
}


