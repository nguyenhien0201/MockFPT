#include "Matrix.h" 
#include<iostream>
#include<string>
#include"MyConsole.h"

#define ROWS 10
#define COLS 10

using namespace std;
#pragma once
//class ban co, cung cap function de cap nhat currentstatus
//value current status luu bang matrix
//ke thua matrix de luu status of table va class myConsole de ve
class Table 
{
public:
	Matrix* status;
	//ham tao table 10x10
	Table();

	//hien thi ban co caro len console
	void display();
	//hien thi lai trang thai, voi dau vao ma tran trang thai, ve nhieu quan co 
	void draw(Matrix& currentStatus);

	//them 1 trang thai x row, y col, ve 1 quan co
	void draw(short x, short y, short value);
};

