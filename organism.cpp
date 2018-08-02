#include "organism.h"
#include <iostream>
using namespace std;

//constructor
Organism::Organism(int x, int y, int turns, bool moved, string s): x(x), y(y), turnsCount(turns), moved(moved), type(s) {};

//virtual functions, throw warning if we try to call them
void Organism::move(Organism*** grid, int& antcount, int& doodlecount) {
	cout << "Error: called virtual function Organism.move(grid)" << endl;
	exit(1);
}
void Organism::breed(Organism*** grid, int& antcount, int& doodlecount) {
	cout << "Error: called virtual function Organism.breed(grid)" << endl;
	exit(1);
}

void Organism::print() {
	cout << "Error: called virtual function Organism.print()" << endl;
	exit(1);
}

int Organism::search(Organism*** grid, int x, int y) {
	//Given organism position, return direction in which nullptr exists. If no neighboring nullptr, return -1.
	//this is going to be used for breed functions that look for nullptr around organism
	//1 is moving up x-axis, 2 is moving up y-axis, 3 is moving down x-axis, 4 is moving down y-axis
	if (x + 1 < BOARD_SIZE && grid[x + 1][y] == nullptr) {
		return 1;
	} else if (y + 1 < BOARD_SIZE && grid[x][y + 1] == nullptr) {
		return 2;
	} else if (x - 1 > -1 && grid[x - 1][y] == nullptr) {
		return 3;
	} else if (y - 1 > -1 && grid[x][y - 1] == nullptr) {
		return 4;
	} else {
		return -1;
	}
}

void Organism::erase() {
	delete this;

}