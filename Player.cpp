#include <iostream>
#include <string>
#include "Player.h"
#include "Bomb.h"
#include "Board.h"

using namespace std;

Player::Player(string playerName, string boardFilename) : board(Board(boardFilename))
{	
	name = playerName;
}

void Player::showBoard() const
{
	Board tabuleiro(board);
	tabuleiro.display();
}

Bomb Player::getBomb() const
{
	return Bomb();
}