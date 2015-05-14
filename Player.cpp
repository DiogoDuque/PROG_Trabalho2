#include <iostream>
#include <string>
#include "Board.h"
#include "Player.h"

using namespace std;

Player::Player(string playerName, string boardFilename)
{
	name=playerName;
	board=boardFilename;
}

void Player::showBoard() const
{
	Board tabuleiro(board);
	tabuleiro.display();
}

Bomb Player::getBomb() const;
{

}