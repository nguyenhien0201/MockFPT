#include<list>
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
	list<Position> marked;
	Position m_start = { 0,0 };
	Position m_end;
	short m_winCondition = 2;
	
	//tra ve ma tran con cua status, duoc xu li tu toa do (x,y)
	Matrix* process(short x, short y);
	void easyProcess(); //easy level
	void normalProcess();//normal level
	void hardProcess();//hard level
	void analysisStatus();
	//tim nuoc di tot nhat
	void bestMove(Matrix* m);
	short minimax(Matrix* m, short depth, bool isMaximizing, short x, short y);
public:
	Matrix* status; //ma tran trang thai ban co
	short m_lever; 
	Position previous; // toa do ma human vua nhap
	
	short m_x, m_y;//buoc di bot chon
	
	MyBot() {}

	MyBot(short level, Matrix* m);
	~MyBot() { delete status; }
	
	void generateMove();
};

