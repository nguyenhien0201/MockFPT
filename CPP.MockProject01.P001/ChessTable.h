#include "Matrix.h" 
#include<iostream>
#include<string>
#include"MyConsole.h"

#define ROWS 10
#define COLS 10
#define CONDITION_WIN 3
using namespace std;
#pragma once
//class ban co, cung cap function de cap nhat currentstatus
//value current status luu bang matrix
//ke thua matrix de luu status of ChessTable va class myConsole de ve
class ChessTable 
{
	//toa do diem dau cua ChessTable, tinh theo box
	short m_X; // row
	short m_Y; // col
public:
	Matrix* status;
	//ChessTable 10x10, goc (0,0)
	ChessTable();
	//ham tao ChessTable 10x10, dich row col (dich theo box)
	ChessTable(short row, short col);

	//hien thi ban co caro len console
	void display();
	//hien thi lai trang thai, voi dau vao ma tran trang thai, ve nhieu quan co 
	void draw(Matrix& currentStatus);
	//di den o co row col
	void gotoBox(short row, short col);
	//them 1 trang thai x row, y col, ve 1 quan co
	void draw(short x, short y, short value);
	//x y la toa do vua duoc chon 
	int checkWin(Matrix* m, int x, int y);
};

