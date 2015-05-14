#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <ctime>
#include <clocale>
#include <sys/stat.h>
#include "Board.h"
#include "Ship.h"
#include "types.h"

using namespace std;

Board::Board(const string &filename)
{
	ifstream file(filename);
	string absorve;

	file >> numLines >> absorve >>numColumns;
	file.ignore(1000, '\n');
	while (!file.eof())
	{	
		char symbol;
		PositionChar position;
		char orientation;
		unsigned int size;
		unsigned int color;

		file >> symbol >> size >> position.lin >> position.col >> orientation >> color;

		if (file.fail())
		{
			cerr << "Ocorreu um erro durante a leitura do ficheiro!";
			exit(1);
		}
		file.ignore(1000, '\n');
		
		ships.push_back(Ship(symbol,position, orientation, size, color));
	}

	file.close();
	int i = 1;

	board.resize(numLines);								
	for (int i = 0; i < numLines; i++)
		board[i].resize(numColumns);

	for (int i = 0; i < numLines; i++)
	{
		for (int j = 0; j < numColumns; j++)
			board[i][j] = -1;
	}
}
PositionInt Board::getposition(int value) const
{
	PositionInt position = ships[value].getposition();
	return position;
}
char Board::getorientation(int value) const
{
	char orientation = ships[value].getorientation();
	return orientation;
}
bool Board::outoftheboard(const Ship &s) const
{
	Ship ship = s;
	unsigned int size = ship.getsize();
	struct PositionInt position = ship.getposition();
	char orientation = ship.getorientation();

	if (((position.lin >= (int)board[board.size() - 1][0]) || (position.lin <= (int)board[1][0])) || ((position.col >= (int)board[0][board[0].size() - 1])
		|| (position.col <= (int)board[0][1])) || ((orientation == 'V') && ((position.lin + size - 1) >= (int)board[board.size() - 1][0])) ||
		((orientation == 'H') && ((position.col + size - 1) >= (int)board[0][board[0].size() - 1])))
		return true;
	else
		return false;

}
bool Board::overboat(const Ship &s) const
{
	Ship ship = s;
	unsigned int size = ship.getsize();
	struct PositionInt position = ship.getposition();
	char orientation = ship.getorientation();
	
	int i = 0;
	if (orientation == 'H')
	{
		while (!false && i <= size)
		{
			if (board[position.lin][position.col + i] != '.')
				return true;
			i++;
		}
	}
	else
	{
		while (!false && i <= size)
		{
			if (board[position.lin + i][position.col] != '.')
				return true;
			i++;
		}
	}
	return false;
}
void Board::newship(const Ship &ship, int index)
{
	PositionInt position = ship.getposition();
	unsigned size = ship.getsize();

	if (ship.getorientation() == 'H')
	{
		for (unsigned i = position.col; i < position.col + size; i++)
		{
			char status_point = ship.getstatus(i - position.col);			// status of a specific part of the ship
			if (status_point == toupper(status_point))
				board[position.lin][i] = index;
			else
				board[position.lin][i] = -1;
		}
	}
	else
	{
		for (unsigned i = position.lin; i < position.lin + size; i++)
		{
			char status_point = ship.getstatus(i - position.lin);
			if (status_point == toupper(status_point))
				board[i][position.col] = index;
			else
				board[i][position.col] = -1;
		}
	}
}
void Board::deleteship(PositionInt position, char orientation, unsigned size)
{
	if (orientation == 'H')
	{
		for (unsigned i = position.col; i < position.col + size; i++)
			board[position.lin][i] = -1;
	}
	else
	{
		for (unsigned i = position.lin; i < position.lin + size; i++)
			board[i][position.col] = -1;
	}
}
void Board::moveShips()
{
	for (size_t i = 0; i < ships.size(); i++)
	{
		PositionInt position = ships[i].getposition();
		char orientation = ships[i].getorientation();

		ships[i].moveRand();
		if (outoftheboard(ships[i]) || overboat(ships[i]))
		{
			ships[i].setorientation(orientation);
			ships[i].setposition(position);
		}
		else
		{
			deleteship(position, orientation, ships[i].getsize());
			newship(ships[i], i);
		}
	}
}
bool Board::attack(const Bomb &b)
{
	PositionChar Positionbombchar = b.getTargetPosition();
	PositionInt Positionbombint;
	Positionbombint.lin = (int)(Positionbombchar.lin - 'A');
	Positionbombint.col = (int)(Positionbombchar.col - 'a');

	int value = board[Positionbombint.lin][Positionbombint.col];
	if (value = -1)
		return false;
	else
	{
		PositionInt position = getposition(value);
		char orientation = getorientation(value);

		size_t index;
		if (orientation == 'H')
			index = Positionbombint.col - position.col;
		else
			index = Positionbombint.lin - position.lin;
		return true;
	}

}

void Board::display() const
{
		setcolor(WHITE, BLACK);
		cout << " ";
		for (int i = 0; i < numColumns; i++)
		cout << setw(2) << (char)(i + 'a');
		cout << endl;

		for (int i = 0; i < numLines; i++)
		{
			setcolor(WHITE, BLACK);
			cout << (char)(i + 'A');
			setcolor(BLACK, LIGHTGRAY);
			cout << " ";
			for (int j = 0; j < numColumns; j++)
			{
				unsigned int k = 0;
				bool thereship;			
				if (board[i][j] == -1)
				{
					setcolor(BLUE, LIGHTGRAY);
					thereship = false;
				}
				else
				{
					while (k != board[i][j])
						k++;
					setcolor(ships[k].getcolor(), LIGHTGRAY);
					thereship = true;
				}

				if (thereship)
					cout << ships[k].getsymbol();
				else
					cout << '.';
				cout << " ";
			}
			cout << endl;
		}

		cout << endl;
		setcolor(WHITE, BLACK);

}

void Board::show() const
{

}

