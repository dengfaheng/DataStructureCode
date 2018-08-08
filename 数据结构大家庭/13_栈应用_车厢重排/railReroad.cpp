#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include "../09_Õ»_Êı×éÃèÊö/arrayStack.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class railReroad
{
public:
	railReroad() {}
	railReroad(int theNumberOfCars, int theNumberOfTracks) : numberOfCars(theNumberOfCars), numberOfTracks(theNumberOfTracks)
	{
		track = new arrayStack<int>[numberOfTracks + 1];
	}
	~railReroad()
	{
		delete[] track;
	}

	void outputFromHoldingTrack()
	{
		track[itsTrack].pop();
		cout << "Move car " << smallestCar << " from holding track" << itsTrack << " to output track" << endl;

		smallestCar = numberOfCars + 2;
		for (int i = 1; i <= numberOfTracks; i++)
		{
			if (!track[i].empty() && (track[i].top() < smallestCar) )
			{
				smallestCar = track[i].top();
				itsTrack = i;
			}
		}
	}

	bool putInHoldingTrack(int c)
	{
		int bestTrack = 0;
		bestTop = numberOfCars + 1;

		for (int i = 1; i <= numberOfTracks; i++)
		{
			if (!track[i].empty())
			{
				int topCar = track[i].top();
				if (c < topCar && topCar < bestTop)
				{
					bestTop = topCar;
					bestTrack = i;
				}
			}
			else
			{
				if (bestTrack == 0)
				{
					bestTrack = i;
				}
			}
			
		}
		if (bestTrack == 0) return false;

		track[bestTrack].push(c);
		cout << "Move car " << c << " from input track to holding track " << bestTrack << endl;

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
	arrayStack<int> * track;
	int numberOfCars;
	int numberOfTracks;
	int smallestCar;
	int itsTrack;
	int bestTop;
};



int main()
{
	railReroad train(9, 3);
	int a[10] = { 0 , 5, 8, 1, 7, 4, 2, 9, 6, 3 };
	train.railroad(a);

	cin.get();
	return 0;
}