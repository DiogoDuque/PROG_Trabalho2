#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <sys/stat.h>
#include <ctime>
#include "Player.h"
#include "types.h"

using namespace std;


//Ecra inicial (animacao BATALHA NAVAL)
void initialScreen()
{
	vector<string> line;
	line.push_back("@@@@    @@@   @@@@@   @@@   @      @   @   @@@\n");
	line.push_back("@   @  @   @    @    @   @  @      @   @  @   @\n");
	line.push_back("@@@@   @@@@@    @    @@@@@  @      @@@@@  @@@@@\n");
	line.push_back("@   @  @   @    @    @   @  @      @   @  @   @\n");
	line.push_back("@@@@   @   @    @    @   @  @@@@@  @   @  @   @\n\n\n");
	line.push_back("@   @   @@@   @   @   @@@   @\n");
	line.push_back("@@  @  @   @  @   @  @   @  @\n");
	line.push_back("@ @ @  @@@@@  @   @  @@@@@  @\n");
	line.push_back("@  @@  @   @   @ @   @   @  @\n");
	line.push_back("@   @  @   @    @    @   @  @@@@@\n\n\n");
	line.push_back("Feito por: Miriam Goncalves e Diogo Duque\n");
	line.push_back("\n");
	line.push_back("\n");
	int t1 = clock(), t2, i = 0;
	while (i<13)
	{
		t2 = clock();
		if (t2 - t1>550)
		{
			cout << line[i];
			i++;
			t1 = t2;
		}
	}

}

//Menu principal
int mainMenu()
{
	char option = '2';
	while (option == '2')
	{
		option = 'a';
		while (option != '1' && option != '2' && option != '3')
		{
			clrscr();
			cout << "-----> Jogo da Batalha Naval <-----\n\n";
			cout << "1 - Jogar\n2 - Top 10\n3 - Sair\n\nInsira a sua escolha: ";
			cin >> option;
		}
		if (option == '1') //Jogar
			return 1;
		if (option == '2') //Highscores
		{
			clrscr();
			cout << "High scores:\n\n";
			string name_highscoresFile, score_highscoresFile;
			ifstream highscoresFile;
			highscoresFile.open("highscores.txt");
			for (int i = 1; i <= 10; i++) //escreve os highscores
			{
				highscoresFile >> name_highscoresFile;
				highscoresFile >> score_highscoresFile;
				cout << i << " - " << name_highscoresFile << " - " << score_highscoresFile << endl;
			}
			highscoresFile.close();
			system("PAUSE");
		}
		if (option == '3') //Exit
			break; //Usei o break e "adiei" o return 3 para que nao aparecesse um warning
	}
	return 3;
}

//Escolhe o nome de um jogador (entre 2 a 5 carateres)
string choosePlayerName(int player_number)
{
	string player_name;
	cout << "\n\n------------------------\nNome do jogador " << player_number << " (2 a 5 Carateres): ";
	cin >> player_name;
	while ((player_name.size() < 2) || (player_name.size() > 5))
	{
		clrscr();
		cout << "ERRO: O nome do jogador deve ter entre 2 a 5 carateres!" << endl;
		cout << "Reinsira o nome do jogador " << player_number << ": ";
		cin >> player_name;
	}
	return player_name;
}

//Funcao auxiliar de choosePlayerBoard
bool exists(const string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

//Escolhe o tabuleiro de um jogador
string choosePlayerBoard(int player_number)
{
	cout << "\n\n------------------------\nNome do ficheiro de tabuleiro do jogador " << player_number << ": ";
	string player_board;
	cin >> player_board;
	while (!exists(player_board))
	{
		clrscr();
		cout << "ERRO: O tabuleiro nao existe!" << endl;
		cout << "Reinsira o nome do tabuleiro " << player_number << ": ";
		cin >> player_board;
	}
	return player_board;
}

//Modifica o registo das pontuacoes e retorna true se ficou no top 10
bool EditHighScores(int score, string player)
{
	ifstream readHighScores;
	readHighScores.open("highscores.txt");
	//Passar highscores para 2 vetores
	vector<string> listNames;
	vector<int> listScores;
	string passador_string;
	int passador_int;
	for (int contador = 0; contador<10; contador++)
	{
		readHighScores >> passador_string;
		listNames.push_back(passador_string);
		readHighScores >> passador_int;
		listScores.push_back(passador_int);
	}
	readHighScores.close();
	//Verificar se novo score deve ser posto
	if (passador_int>score)
		return false;
	//Escolher a posicao do novo score
	vector<int> scores;
	vector<string> names;
	if (score>listScores[0]) //1º lugar
	{
		scores.push_back(score);
		names.push_back(player);
		for (int i = 0; i<9; i++)
		{
			scores.push_back(listScores[i]);
			names.push_back(listNames[i]);
		}
		listScores = scores;
		listNames = names;
	}
	else //2º-10º lugar
	{
		for (int i = 0; i<10; i++)
		{
			if (score>listScores[i]) //Inserir o novo high score
			{
				scores.push_back(score);
				names.push_back(player);
				while (i<9) //inserir o resto do vetor (exceto ultimo elemento)
				{
					scores.push_back(listScores[i]);
					names.push_back(listNames[i]);
					i++;
				}
				break;
			}
			else
			{
				scores.push_back(listScores[i]);
				names.push_back(listNames[i]);
			}
		}
	}
	//reescrever ficheiro
	ofstream highscoresFile("highscores.txt");
	for (int i = 0; i<10; i++)
		highscoresFile << names[i] << " " << scores[i] << endl;
	highscoresFile.close();
	return true;
}

//Fazer jogada // Se ja nao tiver barcos no proprio tabuleiro, nao joga e retorna false
bool play(Player player, Player opponent)
{
	//Verificar se o tabuleiro do player ainda tem barcos (fazer funcao possivelmente)
	//Fazer jogada
	return false;
}

//main
int main()
{
	/*
	initialScreen();
	int option = mainMenu();
	if (option == 3)
		return 0;
	//Escolher se 1 ou 2 players
	char numPlayers = '0';
	while (numPlayers != '1' && numPlayers != '2')
	{
		clrscr();
		cout << "-----> Jogo da Batalha Naval <-----\n\n";
		cout << "Insira a quantidade de jogares:\n1 - Jogador vs CPU\n2 - Jogador vs Jogador\n";
		cin >> numPlayers;
	}

	// definir nomes e tabuleiros dos jogadores
	string player1_name = choosePlayerName(1);
	string player1_board = choosePlayerBoard(1);
	string player2_name;
	if (numPlayers == 1)
	{
		player2_name = "CPU";
		cout << "\n\n------------------------\nNome do jogador 2: CPU";
	}
	else player2_name = choosePlayerName(2);
	string player2_board = choosePlayerBoard(2);
	//criar tabuleiros e jogadores (class player)
	Player player1(player1_name, player1_board);
	Player player2(player2_name, player2_board);
	player1.showBoard();
	//Iniciar jogo
	srand(time(NULL));
	int firstPlayer=rand()%1+1;
	if(firstPlayer==1) //1st Player -> Player 1
	for(int i=1;i<=10;i++) //gameover por turnos
	{
	if(!play(player1,player2))//jogada P1 // Se nao conseguir jogar pq nao tem barcos, break
	break;
	if(!play(player2,player1))//jogada P2 // Se nao conseguir jogar pq nao tem barcos, break
	break;
	}
	else			//1st Player -> Player 2
	for(int i=1;i<=10;i++) //gameover por turnos
	{
	if(!play(player2,player1))//jogada P1 // Se nao conseguir jogar pq nao tem barcos, break
	break;
	if(!play(player1,player2))//jogada P1 // Se nao conseguir jogar pq nao tem barcos, break
	break;
	}
	//GAME OVER (Fazer game over screen)
	*/
	Board tabuleiro("tabuleiro.txt");
	tabuleiro.display();


	return 0;
}