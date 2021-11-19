//#include<limits>
#include"Matrix.h"
#include"ChessTable.h"

//using namespace std;
#define _EASY_ 7
#define _NORMAL_ 8
#define _HARD_ 9
#define MAX 10
#define MIN -MAX
#define _INFINITY_ 2147483647;
#pragma once
const short ai = 2;
const short human = 1;

struct Position {
	short x, y;
};
class MyBot
{

	Position m_start = { 0,0 };
	Position m_end;
	short m_winCondition = 2;
	
	Matrix* process(short x, short y);
	void easyProcess();
	void normalProcess();
	void hardProcess();
	//void analysis(Matrix* m, short& available);

	short minimax(Matrix* m, short depth, bool isMaximizing, short x, short y);
public:
	Matrix* status;
	short m_lever;
	Position previous;
	
	short m_x, m_y;
	
	MyBot() {}

	MyBot(short level, Matrix* m) { m_lever = level; status = m; }
	~MyBot() { delete status; }
	

	void generateMove();
	
	void bestMove(Matrix* m);
	
};

