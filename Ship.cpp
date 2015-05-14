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
		for (unsigned int i = 0; i < size; i++)
		{
			status[i] = symbol;
		}
}
char Ship::getsymbol()
{
	return symbol;
}
char Ship::getorientation()
{
	return orientation;
}

unsigned int Ship::getsize()
{
	return size;
}
unsigned int Ship::getcolor()
{
	return color;
}

struct PositionInt Ship::getposition()
{
	return position;
}

bool Ship::move(char direction, bool rotate, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax) // moves the boat (SEE NOTES)
{
	// simular o movimento do barco
	PositionInt simulatedPosition = position;
	switch (direction)
	{						
	case 'N':
	{
		simulatedPosition.lin--;
		break;
	}
	case 'S':
	{
		simulatedPosition.lin++;
		break;
	}
	case 'W':
	{
		simulatedPosition.col--;
		break;
	}
	case 'E':
	{
		simulatedPosition.col++;
		break;
	}
	default:
		return false;
	} 

	if ((simulatedPosition.lin<lineMin) || (simulatedPosition.col<columnMin) || (simulatedPosition.lin>lineMax) || (simulatedPosition.col>columnMax))
		return false;

	if (rotate == true)
	{
		if (orientation == 'H')
			orientation = 'V';
		else orientation = 'H';
	}

		switch (direction)
	{
		case 'V':
		{
			if (simulatedPosition.lin + size - 1 > lineMax)
				return false;
				break;
		}
		case 'H':
		{
			if (simulatedPosition.col + size - 1 > columnMax)
				return false;
			break;
		}
		default:
			return false;
	}
	position = simulatedPosition;
	return true;
}
bool Ship::moveRand(unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax) // moves the ship randomly
{
	srand((unsigned int) time(NULL));
	char direction;
	int randomDirection = rand() % 5;
	switch (randomDirection)
	{
	case 0:
	{
		direction = '!'; //Nao mexe
		break;
	}
	case 1:
	{
		direction = 'N';
		break;
	}
	case 2:
	{
		direction = 'S';
		break;
	}
	case 3:
	{
		direction = 'W';
		break;
	}
	case 4:
	{
		direction = 'E';
		break;
	}
	}

	bool rotate;
	if (rand() % 2 == 0)
		rotate = false;
	else rotate = true;
	if (move(direction, rotate, lineMin, columnMin, lineMax, columnMax) == true)
		return true;
	return false;
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