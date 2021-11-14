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
	int **v;
	myStatus _status = NONE;
	int rows, cols;
public:
	
	Matrix();
	Matrix(int r, int c);
	Matrix(Matrix &a);
	~Matrix();

	//copy value of a to this
	void copy(Matrix a);
	//add value in maxtrix[row][col]
	void add(short row, short col, short value);
	//print value of matrix
	void display();
	friend Matrix operator + (Matrix a, Matrix b);
};





