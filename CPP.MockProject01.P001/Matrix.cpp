#include "Matrix.h"

Matrix::Matrix()
{
	int i, j;
	/*cout << "Nhap so hang : "; cin >> rows;
	cout << "Nhap so cot : "; cin >> cols;
	if (!(checkInput(rows) && checkInput(cols))) exit(0);*/

	v = new int *[rows];
	for (i = 0; i < rows; i++)
		v[i] = new int[cols];
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
		{
			cout << "v[" << i << j << "]: ";
			cin >> v[i][j];
		}
}
Matrix::Matrix(int r, int c)
{

	rows = r; cols = c;
	v = new int *[rows];
	for (int i = 0; i < rows; i++)
		v[i] = new int[cols];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			v[i][j] = NULL;
		}
}
Matrix::Matrix(Matrix &a)
{
	rows = a.rows; cols = a.cols;
	v = new int *[rows];
	for (int i = 0; i < rows; i++)
		v[i] = new int[cols];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			v[i][j] = a.v[i][j];
}
Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
		delete v[i];
	delete v;
}

void Matrix::copy(Matrix a) {
	for (int i = 0; i < a.rows; i++)
		for (int j = 0; j < a.cols; j++)
			v[i][j] = a.v[i][j];
	//cap nhat trang thai, value changed
	_status = VALUE_CHANGED;
}
void Matrix::add(short i, short j, short value) {
	if (i < rows && j < cols) {
		v[i][j] = value;
		//cap nhat trang thai value changed
		_status = VALUE_CHANGED;
	}
		
}
void Matrix::display()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cout << v[i][j] << "\t";
		cout << endl;
	}
}

Matrix operator + (Matrix a, Matrix b)
{
	int i, j;
	Matrix c = a;
	for (i = 0; i < a.rows; i++)
		for (j = 0; j < a.cols; j++)
			c.v[i][j] = a.v[i][j] + b.v[i][j];
	return c;
}

