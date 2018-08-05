#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "../03_线性表_链式描述/chain.h"
#include "../03_线性表_链式描述/chain.cpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct studentRecord
{
	int score;
	string name;

	studentRecord() {}
	studentRecord(int theScore, string theName) :score(theScore), name(theName) {}

	int operator != (const studentRecord & x) const
	{
		return (score != x.score);
	}
	operator int() const { return score; }
};

//override out
ostream & operator<<(ostream & out, const studentRecord & x)
{
	out << x.name << "  " << x.score << endl;
	return out;
}

void binSort(chain<studentRecord> & theChain, int range)
{
	chain<studentRecord> * bin = new chain<studentRecord>[range + 1];  // 0 to range
	int numberOfElements = theChain.size();

	for (int i = 0; i < numberOfElements; i++)
	{
		studentRecord record = theChain.get(0);
		theChain.erase(0);

		bin[record.score].insert(0, record);
	}
	for (int j = range; j >= 0; j--)
	{
		while (!bin[j].empty())
		{
			studentRecord record = bin[j].get(0);
			bin[j].erase(0);
			theChain.insert(0, record);
		}
	}

	delete[] bin;
}

int main()
{
	srand(time(0));
	chain<studentRecord> students;
	studentRecord someOne;
	for (int i = 0; i < 100; i++)
	{
		char Name = i % 26 + 'A';
		someOne.name = Name;
		someOne.score = rand() % 101;
		students.insert(0, someOne);
	}

	binSort(students, 100);
	cout << "  ";
	students.output(cout);

	cin.get();

	return 0;
}