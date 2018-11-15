#include "../18_队列_数组描述/arrayQueue.h"
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
		//将编号最小的车厢从缓冲轨道移到出轨道
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
		//为车厢c寻找最合适的缓冲轨道
		//初始化
		int bestTrack = 0,  //目前最合适的缓冲轨道
			bestLast = 0;   //取bestTrack中最后的车厢

		//扫描缓冲轨道
		for (int i = 1; i <= numberOfTracks; i++)
		{
			if (!track[i].empty())
			{//轨道i不为空
				int lastCar = track[i].back();
				if (c > lastCar && lastCar > bestLast)
				{
					bestLast = lastCar;
					bestTrack = i;
				}
			}
			else
			{//缓冲轨道为空
				if (bestTrack == 0)
				{
					bestTrack = i;
				}
			}

		}
		if (bestTrack == 0) return false; //没有可用的轨道

		track[bestTrack].enqueue(c);
		cout << "Move car " << c << " from input track to holding track " << bestTrack << endl;
		//更新
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