#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <list>
#include "ChessTable.h"
#include "MyConsole.h"
#include "MyBot.h"
#include "Player.h"
#define NUMBER_OF_GAME_REPLAY 3
#define MAX_PLAYERS 10

using namespace std;
#pragma once
class MyGame
{
	list<Position> replayMoves;
	Matrix** replayGames;
	Player* players;
public:

	MyGame();

	void Start();
	void endGame();

	void mainMenu(WORD color);
	void menuPlayWithBOT(WORD color);
	void backMainMenu(bool Clean);

	void playWithPlayer();
	void playWithBot(short level);

	void Guide();
	void saveMove(short x, short y);
	void saveGame(Matrix* m);
	void displayHistory(Matrix* m, int i);
	void replayLastGame();
	void replay();

	int playerCount();
	void savePlayerToBuffer(Player p);
	void playerInfo();
};