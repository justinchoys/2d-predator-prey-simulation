#pragma once
#ifndef DOODLEBUG_H
#define DOODLEBUG_H

class Doodlebug : public Organism {
public:
	//constructor
	Doodlebug(int x, int y);

	virtual void move(Organism*** grid, int& antcount, int& doodlecount);
	virtual void breed(Organism*** grid, int& antcount, int& doodlecount);
	virtual void print();

	void setStarve(int count) { starveCount = count; };
	int getStarve() { return starveCount; }
		
private:

	int search(Organism*** grid, int x, int y, string s); // overloaded search for type s
	int starveCount = 0;
};

#endif // !DOODLEBUG_H
