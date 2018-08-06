#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include "../03_���Ա�_��ʽ����/chain.h"
#include "../03_���Ա�_��ʽ����/chain.cpp"
#include "../01_�����쳣��/illegalParameterValue.h"

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
	//�� ��B���뵽A����ȥ
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
		//���Ҿ���theElementԪ�ص���
		return equivClass[theElement];
	}

	~unionFindSet()
	{
		delete[] equivClass;
	}

};
//��������
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

//����output����
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
	binSort(machineTasks, maxTime-1);//����ʼʱ�� ��������
	//ʱ��λ�����i-1 ~ i, ����1 <= i <= maxTime
	unionFindSet nearest(maxTime);  //equivClass[k] ��ʾ����ʱ��� i, ����i ����<= k ��Χ������ i ��
	machineTasks.output(cout);

	while (!machineTasks.empty())
	{
		TASK task = machineTasks.get(0);
		machineTasks.erase(0);
		
		int et = nearest.findClass(task.end_time); //���ڽ���ʱ�䷶Χ�����Ŀ���ʱ���
		int ett = nearest.findClass(et - 1);  //��������� �ϲ�et��et-1����
		if (et == 0) //��������ʧ��
		{
			continue;
		}
		ta[et - 1] = task;//��������
		nearest.unionClass(ett, et);//�ϲ����鼯
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