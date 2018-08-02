#include <cstdlib>
#include <ctime>
#include <iostream>
#include "organism.h"
#include "ant.h"
#include "doodlebug.h"
using namespace std;


/* Write a program to implement this simulation and draw the world using ASCII characters of “o” for an ant and “X” for a doodlebug or "-" 
for an empty space. Create a class named Organism that encapsulates basic data common to both ants and doodlebugs. This class should have a
virtual function named move that is defined in the derived classes of Ant and Doodlebug. You may need additional data structures to keep 
track of which critters have moved. */


Organism *** create(int antcount, int doodlecount, int boardsize);
void display(Organism*** grid, int stepcounter, int antcount, int doodlecount);
void step(Organism*** grid, int& antcount, int& doodlecount);
void eraseBoard(Organism*** grid);

int main() {

	char input;
	int stepcounter = 0;
	int ants = ANT_COUNT;
	int doodles = DOODLE_COUNT;
	srand((unsigned int)time(0));

	cout << "Initializing grid with " << ANT_COUNT << " Ants and " << DOODLE_COUNT << " Doodlebugs..." << endl;
	
	Organism***	grid = create(ANT_COUNT, DOODLE_COUNT, BOARD_SIZE);
	display(grid, stepcounter, ants, doodles);
	while (ants != 0 && doodles != 0)	{
		//prompt user to press enter
		
		cout << "Press Enter to Continue, 'q' to exit" << endl;
		
		//textbook example Week 10
		cin.get(input);
		while (input != '\n' && input != 'q') {
			cin.get(input);
		}
		
		if (input == 'q'){
			break;
		}

		stepcounter++;
		
		//simulate timestep (move doodle, breed doodle, move ant, breed ant, update organismcount/moved/survived
		step(grid, ants, doodles);

		//display updated board
		display(grid, stepcounter, ants, doodles);

	}
		
	cout << "----------Simulation ended----------" << endl;

	eraseBoard(grid);

	return 0;
}


Organism*** create(int antcount, int doodlecount, int boardsize) {
	//create pointer to 20x20 array of Organisms
	//reference: int* arr = new int[20] // create ptr arr that points to 20 size array
	//int**arr = new int*[20]// create ptr arr that points to size 20 array full of pointers
	
	Organism*** grid = new Organism**[BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++) {
		grid[i] = new Organism*[BOARD_SIZE];
	}

	//initialize all entries to point to nullptr, cannot instantiate Organism bc virtual
	for (int i = 0; i < BOARD_SIZE; i++) { 
		for (int j = 0; j < BOARD_SIZE; j++) {
			grid[i][j] = nullptr;
		}
	}
	
	//populate grid with ants and doodlebugs
	int ants = 0, doodles= 0;
	int x, y;
	
	while (ants < antcount) {
		x = rand() % BOARD_SIZE;
		y = rand() % BOARD_SIZE;
		if (grid[x][y] == nullptr)	{
			grid[x][y] = new Ant(x, y);
			ants++;
		}
	}

	while (doodles < doodlecount) {
		x = rand() % BOARD_SIZE;
		y = rand() % BOARD_SIZE;
		if (grid[x][y] == nullptr) {
			grid[x][y] = new Doodlebug(x, y);
			doodles++;
		}
	}
	
	return grid;
}

void display(Organism*** grid, int stepcounter, int antcount, int doodlecount) {
	cout << "Time Step: " << stepcounter << " | Ant count: " << antcount << " | Doodlebug count: " << doodlecount << endl;
	cout << endl;

	//cout << "\t0123456789*123456789"<<endl; //printing coordinates for ease of tracking

	for (int x = 0; x < BOARD_SIZE; x++) {
		//cout << x<< "\t";
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (grid[x][y] == nullptr) { 
				cout << "-"; //if pointer points to nullptr, else print appropriate symbol
			} else {
				grid[x][y]->print(); //print is virtual function so it will depend on type of calling object
			}
		}
		cout << endl;
	}

	cout << endl;
	cout << endl;

	/*
	//report generator (need to have define getStarve/setStarve for Organism class, not Doodlebug, to work)
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (grid[x][y]!= nullptr && grid[x][y]->getType() == "Doodlebug") { 
				cout << grid[x][y]->getType() << " at " << grid[x][y]->getX() << ", " << grid[x][y]->getY() << " | Starve at "<<grid[x][y]->getStarve()<<" | Breed at " << grid[x][y]->getTurns()<<endl;
			}
		}
	}
	cout << endl;
	*/

}

void step(Organism*** grid, int& antcount, int& doodlecount) {

	//reset board so all organisms now have moved variable as false
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (grid[x][y] != nullptr)
				grid[x][y]->setMoved(false);
		}
	}

	//move doodlebugs, those that just moved have Moved status set to true
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (grid[x][y] != nullptr && grid[x][y]->getType() == "Doodlebug" && grid[x][y]->getMoved() == false)
				grid[x][y]->move(grid, antcount, doodlecount);
		}
	}

	//breed doodlebugs, only doodlebugs that have Moved status set to true (those just born have Moved set to false)
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (grid[x][y] != nullptr && grid[x][y]->getType() == "Doodlebug" && grid[x][y]->getMoved() == true)
				grid[x][y]->breed(grid, antcount, doodlecount);
		}
	}

	//move ants
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (grid[x][y] != nullptr && grid[x][y]->getType() == "Ant" && grid[x][y]->getMoved() == false)
				grid[x][y]->move(grid, antcount, doodlecount);
		}
	}

	//breed ants
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (grid[x][y] != nullptr && grid[x][y]->getType() == "Ant" && grid[x][y]->getMoved() == true)
				grid[x][y]->breed(grid, antcount, doodlecount);
		}
	}

}

void eraseBoard(Organism*** grid) {

	//delete all objects and set pointers to nullptr
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (grid[i][j] != nullptr) {
				delete grid[i][j];
				grid[i][j] = nullptr;
			}
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		delete[] grid[i];
		grid[i] = nullptr;
	}

	delete[] grid;
	grid = nullptr;

}