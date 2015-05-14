#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Board.h"
#include "Ship.h"

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
using namespace std;
Board::Board(const string &filename)
{
	ifstream file(filename);
	string absorve;

	file >> numColumns >> absorve >> numLines;
	file.ignore(1000, '\n');

	if (file.fail())
	{
		cerr << "Ocorreu um erro durante a leitura do ficheiro!" << endl;
		exit(1);
	}
	else if ((numLines > 26 || numLines < 1) || (numColumns > 26 || numColumns < 1))
	{
		cerr << "Ocorreu um erro ao inserir as dimensoes do tabuleiro!" << endl;
		exit(1);
	}


	

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

	board[0][0] = ' ';

	while (i <= numColumns)
	{
		board[1][i] = i + 96;
		i++;
	}

	int j = 1;

	while (j <= numLines)
	{
		i = 1;
		while (i <= numColumns)
		{
			board[j][i] = -1;
			i++;
		}
		board[j][0] = j + 64;
		j++;
	}
	
}

bool Board::putShip(const Ship &s)
{
	Ship ship = s;
	unsigned int size = ship.getsize();
	char symbol = ship.getsymbol();
	struct PositionInt position = ship.getposition();
	char orientation = ship.getorientation();

	if (orientation == 'H')
	{
		for (int i = 0; i < size; i++)
			board[position.lin][position.col + i] = symbol;
	}
	else if (orientation == 'V')
	{
		for (int i = 0; i < size; i++)
			board[position.lin + i][position.col] = symbol;
	}

	if (((position.lin >(int) board[board.size() - 1][0]) || (position.lin < (int)board[1][0])) || ((position.col >(int) board[0][board[0].size() - 1])
		|| (position.col < (int)board[0][1])) || ((orientation == 'V') && ((position.lin + size - 1) >(int) board[board.size() - 1][0])) ||
		((orientation == 'H') && ((position.col + size - 1) > (int)board[0][board[0].size() - 1])))
		return true;
		return false;


		int i = 0;
		if (orientation == 'H')
		{
			while (!false && i < size)
			{
				if (board[position.lin][position.col + i] != '.')
					return true;
				i++;
			}
		}
		else
		{
			while (!false && i < size)
			{
				if (board[position.lin + i][position.col] != '.')
					return true;
				i++;
			}
		}
		return false;
}



void Board::moveShips()
{

}

bool Board::attack(const Bomb &b)
{

}

void Board::display() const
{

}

void Board::show() const
{

}
