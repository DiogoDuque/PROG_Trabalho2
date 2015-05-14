#include <iostream>
#include "Ship.h"
#include <ctime>
#include "types.h"

using namespace std;
Ship::Ship()
{
	
}
Ship::Ship(char Symbol, PositionChar Position, char Orientation, unsigned int Size, unsigned int Color)
{
		position.lin = static_cast<int>(Position.lin - 'A');
		position.col = static_cast<int>(Position.col - 'a');
		size = Size;
		color = Color;
		orientation = Orientation;
		symbol = Symbol;
		status = string(size, symbol);
}
char Ship::getsymbol() const
{
	return symbol;
}
char Ship::getorientation() const
{
	return orientation;
}

unsigned int Ship::getsize() const
{
	return size;
}
unsigned int Ship::getcolor() const
{
	return color;
}

struct PositionInt Ship::getposition() const
{
	return position;
}

void Ship::move(char direction, bool rotate) // moves the boat (SEE NOTES)
{
		

		if (direction == 'N')
			position.lin = position.lin - 1;
		else if (direction == 'S')
			position.lin = position.lin + 1;
		else if (direction == 'E')
			position.col = position.col + 1;
		else
			position.col = position.col - 1;

		if (rotate)
		{
			if (orientation == 'H')
				orientation = 'V';
			else
				orientation = 'H';
		}
	

}
char Ship::getstatus(unsigned index) const
{
	return status[index];
}
void Ship::setposition(PositionInt position)
{
	this->position.lin = position.lin;
	this->position.col = position.col;
}
void Ship::setorientation(char orientation)
{
	this->orientation = orientation;
}
void Ship::moveRand()
{	// creates ship's moving parameters

	int randomNumber = rand() % 5;		// generate direction move, equal probabilities
	char direction;

	if (randomNumber == 1)
		direction = 'N';
	else if (randomNumber == 2)
		direction = 'S';
	else if (randomNumber == 3)
		direction = 'E';
	else if (randomNumber == 4)
		direction = 'W';
	else								// doesn't move
		direction = '\0';


	bool rotate = true;
	randomNumber = rand() % 4;			// 25% chance rotating
	if (randomNumber)
		rotate = false;

	move(direction, rotate);
}
bool Ship::attack(size_t partNumber)
{
	if (partNumber >= 0 && partNumber <= size - 1)
	{
		status[partNumber] = tolower(status[partNumber]);
		return true;
	}
	else
		return false;

}
bool Ship::isDestroyed() const
{
	unsigned int c = 0; // contador para o número de minúsculas que encontrar
	for (unsigned int i = 0; i <= size - 1; i++) // ciclo para encontrar minúsculas no status
	{
		if (islower(status[i]))
			c++;
	}
	
	if (c >= size / 2) // verificar se no mínimo metade do barco está destruido
	{
		return true;
	}
	else
		return false;
}

void Ship::show() const
{
	cout << "Symbol: " << symbol << endl;
	cout << "Position: " << position.col << endl << position.lin << endl;
	cout << "orientation: " << orientation << endl;
	cout << "size: " << size << endl;
	cout << "color: " << color << endl;
	cout << "status: " << status << endl;
}