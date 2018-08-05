#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include "../03_线性表_链式描述/chain.h"
#include "../03_线性表_链式描述/chain.cpp"

using std::cout;
using std::cin;
using std::endl;

//根据exp对theNumbers链表进行个位，十位，百位进行排序
void binSort(chain<int> & theNumbers, int exp)
{
	chain<int> * bin = new chain<int>[10];  // 0 to 9
	int numberOfElements = theNumbers.size();

	for (int i = 0; i < numberOfElements; i++)
	{
		int num = theNumbers.get(0);
		theNumbers.erase(0);

		bin[(num / exp) % 10].insert(0, num);
	}
	for (int j = 9; j >= 0; j--)
	{
		while (!bin[j].empty())
		{
			int num = bin[j].get(0);
			bin[j].erase(0);
			theNumbers.insert(0, num);
		}
	}

	delete[] bin;
}

inline int getMaxNumber(chain<int> & theNumbers)
{
	int maxNum = 0, temp;
	for (int i = 0; i < theNumbers.size(); i++)
	{
		temp = theNumbers.get(i);
		if ( maxNum < temp)
		{
			maxNum = temp;
		}
	}

	return maxNum;
}

inline int getBits(int num)
{
	int bits = 0;
	while (num > 0)
	{
		bits++;
		num /= 10;
	}

	return bits;
}

void radixSort(chain<int> & theNumbers)
{
	int maxNum = getMaxNumber(theNumbers);
	int bitsNum = getBits(maxNum);
	int exp = 1;
	for (int i = 1; i <= bitsNum; i++)
	{
		binSort(theNumbers, exp);
		exp *= 10;
	}
}

int main()
{
	chain<int> numbers;
	srand((unsigned int)time(0));
	int num;
	for (int i = 0; i < 100; i++)
	{
		num = rand() % 1000;
		numbers.insert(0, num);
	}
	numbers.output(cout);

	cout << "After the radix sort\n" << endl;
	radixSort(numbers);
	numbers.output(cout);

	cin.get();
	return 0;
}