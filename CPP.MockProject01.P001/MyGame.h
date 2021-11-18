#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

#include "ChessTable.h"
#include "MyConsole.h"
#include "MyBot.h"

#define NUMBER_OF_GAME_REPLAY 3

using namespace std;
#pragma once
class MyGame
{
	Matrix** replayGames;
public:
	
	MyGame();

	void Start();
	void endGame();

	void mainMenu(WORD color);
	void menuPlayWithBOT(WORD color);
	void backMainMenu(bool clean);

	void playWithPlayer();
	void playWithBot(short level);

	void Guild();

	void saveGame(Matrix* m);
	void displayOldGame(Matrix* m, int i);
	void replay();
};