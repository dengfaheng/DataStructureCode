#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include "../03_线性表_链式描述/chain.h"
#include "../03_线性表_链式描述/chain.cpp"
#include "../01_参数异常类/illegalParameterValue.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

struct TASK
{
	string taks_name;
	int start_time;
	int end_time;
	bool operator==(const TASK & t) { return ((start_time == t.start_time) && (end_time == t.end_time)); }
	bool operator!=(const TASK & t) { return ((start_time != t.start_time) && (end_time != t.end_time)); }
};


class unionFindSet
{
protected:
	int *equivClass;
	int numberOfElements;

public:
	unionFindSet(int theNum = 10)
	{
		numberOfElements = theNum;
		equivClass = new int[numberOfElements + 1];
		for (int e= 1; e <= numberOfElements; e++)
		{
			equivClass[e] = e;
		}
		equivClass[0] = 0;
	}
	//并 将B并入到A里面去
	void unionClass(int classA, int classB)
	{
		for (int k = 1; k <= numberOfElements; k++)
		{
			if (equivClass[k] == classB)
			{
				equivClass[k] = classA;
			}
		}
	}

	int findClass(int theElement)
	{
		//查找具有theElement元素的类
		return equivClass[theElement];
	}

	~unionFindSet()
	{
		delete[] equivClass;
	}

};
//箱子排序
void binSort(chain<TASK> & theChain, int range)
{
	chain<TASK> * bin = new chain<TASK>[range + 1];  // 0 to range
	int numberOfElements = theChain.size();

	for (int i = 0; i < numberOfElements; i++)
	{
		TASK task = theChain.get(0);
		theChain.erase(0);

		bin[task.start_time].insertFromHead(task);
	}
	for (int j = 0; j <= range; j++)
	{
		while (!bin[j].empty())
		{
			TASK task = bin[j].get(0);
			bin[j].erase(0);
			theChain.insertFromHead(task);
		}
	}

	delete[] bin;
}

//重载output方法
void chain<TASK>::output(ostream &out) const
{
	for (chainNode<TASK> * currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
	{
		out << std::setw(4) << currentNode->element.taks_name << "  " << std::setw(4) << currentNode->element.start_time << "  " << std::setw(4) << currentNode->element.end_time << endl;
	}
	out << endl;
}

int main()
{
	const int maxTime = 4;

	chain<TASK> machineTasks;
	TASK ta[4] = { {"A", 0, 4}, {"B",0, 4}, {"C", 1, 2}, {"D", 2, 3} };
	for (int i = 0; i < 4; i++)
	{
		machineTasks.insertFromBack(ta[i]);
	}
	binSort(machineTasks, maxTime-1);//按开始时间 降序排序
	//时间段划分是i-1 ~ i, 其中1 <= i <= maxTime
	unionFindSet nearest(maxTime);  //equivClass[k] 表示空闲时间段 i, 其中i 是在<= k 范围内最大的 i ；
	machineTasks.output(cout);

	while (!machineTasks.empty())
	{
		TASK task = machineTasks.get(0);
		machineTasks.erase(0);
		
		int et = nearest.findClass(task.end_time); //找在结束时间范围内最大的空闲时间段
		int ett = nearest.findClass(et - 1);  //分配任务后， 合并et和et-1的类
		if (et == 0) //分配任务失败
		{
			continue;
		}
		ta[et - 1] = task;//分配任务
		nearest.unionClass(ett, et);//合并并查集
	}

	for (int i = 0; i < 4; i++)
	{
		machineTasks.insertFromBack(ta[i]);
	}
	cout << endl;
	machineTasks.output(cout);

	cin.get();
	return 0;
}