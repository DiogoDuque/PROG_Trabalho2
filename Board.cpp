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

void clrscr(void)
{
	COORD coordScreen = { 0, 0 }; // upper left corner
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}
void setcolor(unsigned int color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}
void setcolor(unsigned int color, unsigned int background_color)
	{
		HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
		if (background_color == 0)
			SetConsoleTextAttribute(hCon, color);
		else
			SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN |
			BACKGROUND_RED);
	}
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

	if (((position.lin >= (int) board[board.size() - 1][0]) || (position.lin <= (int)board[1][0])) || ((position.col >= (int) board[0][board[0].size() - 1])
		|| (position.col <= (int)board[0][1])) || ((orientation == 'V') && ((position.lin + size - 1) >=(int) board[board.size() - 1][0])) ||
		((orientation == 'H') && ((position.col + size - 1) >= (int)board[0][board[0].size() - 1])))
		return true;
		return false;


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



void Board::moveShips()
{
}

bool Board::attack(const Bomb &b)
{
	return true;
}



void Board::display() const
{
	Ship ships;

	unsigned int size = ships.getsize();
	char symbol = ships.getsymbol();
	struct PositionInt position = ships.getposition();
	char orientation = ships.getorientation();

	for (unsigned int i = 0; i <= board.size(); i++)
	{
		for (unsigned int j = 0; j <= board[i].size(); j++)
		{
			if (i == 0 || j == 0)
				setcolor(WHITE, BLACK);
			else if (board[i][j] == '.')
				setcolor(BLUE, LIGHTGRAY);
			else
			{
				unsigned int k = 0;
				while (symbol != board[i][j])
				{
					k++;
				}
				setcolor(symbol, LIGHTGRAY);
			}
			board[i][j];

		}
	}
}

void Board::show() const
{
	for (unsigned int i = 0; i <= board.size(); i++)
	{
		for (unsigned int j = 0; j <= board[i].size(); j++)
		{
		cout << board[i][j];
		cout << " ";
		}
		cout << endl;
	}
}

