#include<iostream>
#include<string>
#define	_ERROR_ -15
using namespace std;

#pragma once

class Matrix
{
	bool check(int i, int j) {
		return i < rows && j < cols;
	}
private:
	int rows, cols;

public:
	int **value; //chi dung khi chac chan kg truy cap ngoai matran
	
	//khoi tao toan gia tri NULL
	Matrix(short r, short c);
	
	//
	Matrix();
	Matrix(Matrix &a);
	~Matrix();
	//
	short getRows();
	short getCols();
	short getValue(short row, short col);
	//add value in maxtrix[row][col]
	void add(short row, short col, short v);
	//copy 2 matrix cung cap
	static void copyMatrix(Matrix* a, Matrix* b);
	//copy value of a to this
	void copy(Matrix a);
	//print value of matrix
	void display();

	friend Matrix operator + (Matrix a, Matrix b);
};





