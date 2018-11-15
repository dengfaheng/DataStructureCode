#include "../18_����_��������/arrayQueue.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class railReroad
{
public:
	railReroad() {}
	railReroad(int theNumberOfCars, int theNumberOfTracks) : numberOfCars(theNumberOfCars), numberOfTracks(theNumberOfTracks)
	{
		track = new arrayQueue<int>[numberOfTracks + 1];
	}
	~railReroad()
	{
		delete[] track;
	}

	void outputFromHoldingTrack()
	{
		//�������С�ĳ���ӻ������Ƶ������
		track[itsTrack].dequeue();
		cout << "Move car " << smallestCar << " from holding track" << itsTrack << " to output track" << endl;

		smallestCar = numberOfCars + 2;
		for (int i = 1; i <= numberOfTracks; i++)
		{
			if (!track[i].empty() && (track[i].front() < smallestCar))
			{
				smallestCar = track[i].front();
				itsTrack = i;
			}
		}
	}

	bool putInHoldingTrack(int c)
	{
		//Ϊ����cѰ������ʵĻ�����
		//��ʼ��
		int bestTrack = 0,  //Ŀǰ����ʵĻ�����
			bestLast = 0;   //ȡbestTrack�����ĳ���

		//ɨ�軺����
		for (int i = 1; i <= numberOfTracks; i++)
		{
			if (!track[i].empty())
			{//���i��Ϊ��
				int lastCar = track[i].back();
				if (c > lastCar && lastCar > bestLast)
				{
					bestLast = lastCar;
					bestTrack = i;
				}
			}
			else
			{//������Ϊ��
				if (bestTrack == 0)
				{
					bestTrack = i;
				}
			}

		}
		if (bestTrack == 0) return false; //û�п��õĹ��

		track[bestTrack].enqueue(c);
		cout << "Move car " << c << " from input track to holding track " << bestTrack << endl;
		//����
		if (c < smallestCar)
		{
			smallestCar = c;
			itsTrack = bestTrack;
		}
		return true;

	}

	bool railroad(int inputOrder[])
	{
		int nextCarToOutput = 1;
		smallestCar = numberOfCars + 1;

		for (int i = 1; i <= numberOfCars; i++)
		{
			if (inputOrder[i] == nextCarToOutput)
			{
				cout << "Move car " << inputOrder[i] << " from input track to output track" << endl;
				nextCarToOutput++;

				while (smallestCar == nextCarToOutput)
				{
					outputFromHoldingTrack();
					nextCarToOutput++;
				}
			}
			else
			{
				if (!putInHoldingTrack(inputOrder[i]))
				{
					return false;
				}
			}
		}
		return true;
	}

private:
	arrayQueue<int> * track;
	int numberOfCars;
	int numberOfTracks;
	int smallestCar;
	int itsTrack;
};

int main()
{
	railReroad train(9, 3);
	int a[10] = { 0 , 5, 8, 1, 7, 4, 2, 9, 6, 3 };
	train.railroad(a);

	cin.get();
	cin.get();

	return 0;
}