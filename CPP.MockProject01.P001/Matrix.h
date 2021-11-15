#include<iostream>
#include<string>

using namespace std;

#pragma once

class Matrix
{
	enum myStatus
	{
		NONE = 0,
		VALUE_CHANGED = 1,
	};
	
private:
	int rows, cols;
	myStatus _status = NONE;
public:
	int **value;
	Matrix();
	//khoi tao mang r hang c cot, chua toan gia tri NULL
	Matrix(short r, short c);
	Matrix(Matrix &a);
	~Matrix();

	//copy value of a to this
	void copy(Matrix a);
	//add value in maxtrix[row][col]
	void add(short row, short col, short v);
	//print value of matrix
	void display();
	friend Matrix operator + (Matrix a, Matrix b);
};





