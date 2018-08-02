#pragma once
#ifndef ANT_H
#define ANT_H
#include <string>
using namespace std;

const int ANT_BREED_COUNT = 3;

class Ant : public Organism {
public:
	//constructor
	Ant(int x, int y);

	virtual void move(Organism*** grid, int& antcount, int& doodlecount);
	virtual void breed(Organism*** grid, int& antcount, int& doodlecount);
	virtual void print();


private:
	//no additional member variables

};

#endif // !ANT_H
