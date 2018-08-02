#include "organism.h"
#include "doodlebug.h"
#include <iostream>
#include <string>
using namespace std;

const int STARVE_COUNT = 3;
const int DOODLE_BREED_COUNT = 8;

Doodlebug::Doodlebug(int x, int y) : Organism(x, y, 0, false, "Doodlebug"), starveCount(0) {}

void Doodlebug::move(Organism*** grid, int& antcount, int& doodlecount) {

	//Every time step, if there is an adjacent ant(up, down, left, or right), then the doodlebug will move to that cell and eat the ant.
	//Otherwise, the doodlebug moves according to the same rules as the ant. Note that a doodlebug cannot eat other doodlebugs.
	//Note: Doodlebug needs to be able to access and mutate Grid
	
	int x = getX(), y = getY();
	int dir; 
	int result = search(grid, x, y, "Ant"); //1 is moving up x-axis, 2 is moving up y-axis, 3 is moving down x-axis, 4 is moving down y-axis, -1 is no Ant found
	bool eat = false; //boolean to see if doodlebug is just moving or eating+moving
	
	if (result != -1)	{ //if there is neighboring ant, then choose that direction
		dir = result;
		eat = true;
		antcount--;
		setStarve(0); //reset starve counter
	} else { //else go in random direction (availability checks are below)
		dir = (rand() % 4) + 1;
		setStarve(getStarve() + 1);
	}

	if (dir == 1 && x + 1 < BOARD_SIZE && (grid[x + 1][y] == nullptr || grid[x + 1][y]->getType() == "Ant")) { //availability check, redundant if there is adjacent ant but required for when search returns -1
		if (eat) {
			delete grid[x + 1][y];
			grid[x + 1][y] = nullptr;
		}
		grid[x + 1][y] = this;
		grid[x][y] = nullptr;
		setX(x + 1);

	} else if (dir == 2 && y + 1 < BOARD_SIZE && (grid[x][y + 1] == nullptr || grid[x][y + 1]->getType() == "Ant")) {
		if (eat) {
			delete grid[x][y + 1];
			grid[x][y + 1] = nullptr;
		}
		grid[x][y + 1] = this;
		grid[x][y] = nullptr;
		setY(y + 1);

	} else if (dir == 3 && x - 1 > -1 && (grid[x - 1][y] == nullptr || grid[x - 1][y]->getType() == "Ant")) {
		if (eat) {
			delete grid[x - 1][y];
			grid[x - 1][y] = nullptr;
		}
		grid[x - 1][y] = this;
		grid[x][y] = nullptr;
		setX(x - 1);

	} else if (dir == 4 && y - 1 > -1 && (grid[x][y - 1] == nullptr || grid[x][y - 1]->getType() == "Ant")) {
		if (eat) {
			delete grid[x][y - 1];
			grid[x][y - 1] = nullptr;
		}
		grid[x][y - 1] = this;
		grid[x][y] = nullptr;
		setY(y - 1);
	}

	/*
	if (result == -1)
		cout << "move ";
	else 
		cout << "eat "; 

	cout << " to " <<getX()  << ", " << getY() << " in direction " << dir << "| starve at " << getStarve() << endl;
	*/

	setMoved(true);
	
	//Starve. If a doodlebug has not eaten an ant within the last three time steps, then at the end of the third 
	//time step it will starve and die. The doodlebug should then be removed from the grid of cells.
	if (getStarve() == STARVE_COUNT) {
		int x = getX(), y = getY();
		delete grid[x][y];
		grid[x][y] = nullptr;
		doodlecount--;
	}
}

void Doodlebug::breed(Organism*** grid, int& antcount, int& doodlecount) {
	//If an Doodlebug survives for three time steps, then at the end of the time step (that is; after moving) the Doodlebug will breed.
	//This is simulated by creat-ing a new Doodlebug in an adjacent (up, down, left, or right) cell that is empty. If there is no empty cell available, then no breeding occurs.
	//Once an off-spring is produced, an Doodlebug cannot produce an offspring until three more time steps have elapsed.
	//Note: Doodlebug needs to be able to access and mutate Grid

	setTurns(getTurns() + 1); // increment turns for breeding

	if (getTurns() == DOODLE_BREED_COUNT) {

		int x = getX(), y = getY();
		int dir; //1 is moving up x-axis, 2 is moving up y-axis, 3 is moving down x-axis, 4 is moving down y-axis
		int result = Organism::search(grid, x, y); //search for empty space
		
		if (result != -1) { //if there is neighboring space to breed, then choose that direction
			dir = result;
			if (dir == 1) {
				grid[x + 1][y] = new Doodlebug(x + 1, y);
			} else if (dir == 2) {
				grid[x][y + 1] = new Doodlebug(x, y + 1);
			} else if (dir == 3) {
				grid[x - 1][y] = new Doodlebug(x - 1, y);
			} else if (dir == 4) {
				grid[x][y - 1] = new Doodlebug(x, y - 1);
			}
			doodlecount++;
		}
		setTurns(0);
	}

}
void Doodlebug::print() {
	cout << "X";
}

int Doodlebug::search(Organism*** grid, int x, int y, string type) {
	//Given doodlebug position, return direction in which ant exists, if no ant. If no neighboring ant, return -1.
	//1 is moving up x-axis, 2 is moving up y-axis, 3 is moving down x-axis, 4 is moving down y-axis
	//check for nullptr first or getType() function will cause error since not defined
	if (x + 1 < BOARD_SIZE && grid[x + 1][y] != nullptr && grid[x + 1][y]->getType() == type) {
		return 1;
	} else if (y + 1 < BOARD_SIZE && grid[x][y + 1] != nullptr && grid[x][y + 1]->getType() == type) {
		return 2;
	} else if (x - 1 > -1 && grid[x - 1][y] != nullptr && grid[x - 1][y]->getType() == type) {
		return 3;
	} else if (y - 1 > -1 && grid[x][y-1] != nullptr && grid[x][y - 1]->getType() == type) {
		return 4;
	} else {
		return -1;
	}
}

