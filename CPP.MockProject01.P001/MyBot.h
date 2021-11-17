#include<limits>
#include"Matrix.h"
#include"ChessTable.h"

//using namespace std;
#define _EASY_ 8
#define _NORMAL_ 16
#define _HARD_ 24
#define MAX 10
#define MIN -MAX
#define _INFINITY_ 2147483647;
#pragma once
const short ai = 2;
const short human = 1;
class MyBot
{

public:
	Matrix* status;
	short m_lever;

	short m_x, m_y;
	MyBot() {}

	MyBot(short level, Matrix* m) { m_lever = level; status = m; }
	/*MyBot(Matrix* m) {
		status = m;
	}*/
	//void generateMove();
	void bestMove();
	short minimax(Matrix* m, short depth, bool isMaximizing, short x, short y);

	//short checkStateGame(Matrix* board, Move mov);
};

