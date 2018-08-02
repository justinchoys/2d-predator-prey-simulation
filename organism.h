#pragma once
#ifndef ORGANISM_H
#define ORGANISM_H
#include <string>
using namespace std;

const int BOARD_SIZE = 20;
const int ANT_COUNT = 100;
const int DOODLE_COUNT = 5;

class Organism {
public:

	Organism(int x, int y, int turns, bool moved, string s); //cannot instantiate Organism object!

	virtual void move(Organism*** grid, int& antcount, int& doodlecount)=0; //pure virtual, so we cannot instantiate Organism object
	virtual void breed(Organism*** grid, int& antcount, int& doodlecount)=0;
	virtual void print()=0;

	int getX() const{ return x; };
	int getY() const{ return y; };
	int getTurns() { return turnsCount; };
	bool getMoved() { return moved; };
	string getType() { return type; };

	void setX(int newX) { x = newX; };
	void setY(int newY) { y = newY; };
	void setTurns(int num) { turnsCount = num; };
	void setMoved(bool status) { moved = status; };
	void setType(string s) { type = s; }

	void erase();

	int search(Organism*** grid, int x, int y); // search for neighboring nullptr
	
	//for testing
	//void setStarve(int n) { starveCount = n; }
	//int getStarve() { return starveCount; }

private:
	int x;
	int y;
	int turnsCount = 0; //default values
	bool moved = false;
	string type; // default value of Organism set to empty
	int starveCount;

};



#endif // !ORGANISM_H
