#include<limits>
#include"Matrix.h"
#include"ChessTable.h"
//using namespace std;
#define _EASY_ 40
#define _NORMAL_ 70
#define _HARD_ 90
#define MAX 10
#define MIN -MAX
#define _INFINITY_ 2147483647;
#pragma once
const short ai = 2;
const short human = 1;
class MyBot
{
	struct Move {
		short x;
		short y;
	};
private:
	Matrix* status;
	short m_lever;
public:
	Move m_move;
	MyBot(){}
	MyBot(short level, Matrix* m) { m_lever = level; status = m; }
	/*MyBot(Matrix* m) {
		status = m;
	}*/
	void generateMove();
	void bestMove();
	short minimax(Matrix* m, short depth, bool isMaximizing);

	//short checkStateGame(Matrix* board, Move mov);
};

