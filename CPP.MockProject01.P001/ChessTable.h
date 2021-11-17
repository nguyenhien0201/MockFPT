#include<iostream>
#include<string>
#include "Matrix.h" 
#include"MyConsole.h"

#define ROWS 3
#define COLS ROWS
#define CONDITION_WIN 2
#define DRAW_GAME 3

using namespace std;
#pragma once
//quan ly ban co
class ChessTable 
{
	//toa do diem dau cua ChessTable, tinh theo box
	short m_X; // row
	short m_Y; // col
public:
	Matrix* status;
	//goc (0,0)
	ChessTable();
	// goc (row, col) (chess box)
	ChessTable(short row, short col);

	void display();
	
	void gotoChessBox(short row, short col);

	void draw(short r, short c, short value); 
	
	bool checkMove(short i, short j);
	/*
	NULL: tiep tuc choi
	0: hoa
	1: player 1 win;
	2: player 2 win;
	*/
	static short checkWinner(Matrix* m, short x, short y);
	/*
	NULL: tiep tuc choi
	0: hoa
	1: player 1 win;
	2: player 2 win;
	*/
	int checkWin(int x, int y);// (x y) la toa do vua duoc chon 

	void draw(Matrix* currentStatus);
};

