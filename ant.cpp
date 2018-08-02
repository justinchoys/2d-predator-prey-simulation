#include "organism.h"
#include "ant.h"
#include <iostream>
using namespace std;

Ant::Ant(int x, int y) : Organism(x, y, 0, false, "Ant") {}

void Ant::move(Organism*** grid, int& antcount, int& doodlecount) {
	// choose random direction using RNG
	//Every time step, randomly try to move up, down, left, or right.
	//If the neighboring cell in the selected direction is occupied or would move the ant off the grid, then the ant stays in the current cell.
	//Note: Ant needs to be able to access and mutate Grid

	int x = getX(), y = getY();
	int dir = (rand() % 4) + 1; //1 is moving up x-axis, 2 is moving up y-axis, 3 is moving down x-axis, 4 is moving down y-axis

	if (dir == 1 && x + 1 < BOARD_SIZE && grid[x + 1][y] == nullptr) { // if space in direction 1 is within bounds and is nullptr, move there, otherwise nothing happens
		grid[x+1][y] = this; //make destination pointer point to this object
		grid[x][y] = nullptr; //set origin pointer to nullptr
		setX(x+1); //change coordinates accordinly
	} else if (dir == 2 && y + 1 < BOARD_SIZE && grid[x][y + 1] == nullptr)	{
		grid[x][y+1] = this;
		grid[x][y] = nullptr;
		setY(y+1);
	} else if (dir == 3 && x - 1 > -1 && grid[x-1][y] == nullptr) {
		grid[x-1][y] = this;
		grid[x][y] = nullptr;
		setX(x-1);
	} else if (dir == 4 && y - 1 > -1 && grid[x][y-1] == nullptr) {
		grid[x][y-1] = this;
		grid[x][y] = nullptr;
		setY(y-1);
	}

	//note if any of the if/elseif condition fails, then ant will NOT move

	setMoved(true);
}

void Ant::breed(Organism*** grid, int& antcount, int& doodlecount) {
	//If an ant survives for three time steps, then at the end of the time step (that is; after moving) the ant will breed.
	//This is simulated by creating a new ant in an adjacent (up, down, left, or right) cell that is empty. If there is no empty cell available, then no breeding occurs.
	//Once an off-spring is produced, an ant cannot produce an offspring until three more time steps have elapsed.
	//Note: Ant needs to be able to access and mutate grid

	setTurns(getTurns() + 1); // increment turns for breeding

	if (getTurns() == ANT_BREED_COUNT) {

		int x = getX(), y = getY();
		int dir; //1 is moving up x-axis, 2 is moving up y-axis, 3 is moving down x-axis, 4 is moving down y-axis
		int result = search(grid, x, y); //search for empty space, if search returns -1, it means there is no space, and Ant does NOT breed

		if (result != -1) { //if there is neighboring space to breed, then choose that direction, note board limit and nullptr checks have been done inside search function
			dir = result;
			if (dir == 1) {
				grid[x + 1][y] = new Ant(x + 1, y);
			} else if (dir == 2) {
				grid[x][y + 1] = new Ant(x, y + 1);
			} else if (dir == 3) {
				grid[x - 1][y] = new Ant(x - 1, y);
			} else if (dir == 4) {
				grid[x][y - 1] = new Ant(x, y - 1);
			}
			antcount++;
		}
		setTurns(0); //reset turn counter for breeding
	}
}

void Ant::print() {
	cout << "O";
}