#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <list>
#include "ChessTable.h"
#include "MyConsole.h"
#include "MyBot.h"

#define NUMBER_OF_GAME_REPLAY 3

using namespace std;
#pragma once
class MyGame
{
	list<Position> replayMoves;
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
	void saveMove(short x, short y);
	void saveGame(Matrix* m);
	void displayHistory(Matrix* m, int i);
	void replayLastGame();
	void replay();
};