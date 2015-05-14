#include <vector>
#include <string>
#include "Bomb.h"
#include "Ship.h"
#include "types.h"
#ifndef _Board
#define _Board 

using namespace std;
class Board
{
public:
	Board(const string &filename); // loads board from file 'filename'
	PositionInt getposition(int value) const;
	void putShip(const Ship &s);
	char getorientation(int value) const;
	void newship(const Ship &ship, int index);
	void deleteship(PositionInt position, char orientation, unsigned size);
	bool outoftheboard(const Ship &s) const; // check if the ship is not out of bonds
	bool overboat(const Ship &s) const; // check if the ship is not over another ship
	void moveShips(); // tries to randmonly move all the ships of the fleet
	bool attack(const Bomb &b);
	void display() const; // displays the colored board during the game
	void show() const; // shows the attributes of the board (for debugging)

private:
	int numLines, numColumns; // redundant info …
	vector<Ship> ships; // ships that are placed on the board
	vector<vector<int>> board; // each element indicates
	// the index of a ship in the 'ships' vector
	// (in the range 0..ships.size()-1) ;
	// -1 is used to represent the sea
};
#endif