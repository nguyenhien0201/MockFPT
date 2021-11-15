#include "ChessTable.h"

ChessTable::ChessTable() {
	m_X = 1;
	m_Y = 1;
	status = new Matrix(ROWS, COLS);
}
ChessTable::ChessTable(short row, short col) {
	m_X = row;
	m_Y = col;
	status = new Matrix(ROWS, COLS);
}
void ChessTable::display() {
	//in cac index of ban co
	for (int i = 0; i < COLS; i++) {
		DrawChess(m_X - 1, m_Y + i, i + 48);
		DrawChess(m_X + i, m_Y - 1, i + 48);
	}

	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++) {
			DrawBox(i + m_X, j + m_Y);
		}
	gotoBox(ROWS + m_X, m_Y);
}

void ChessTable::draw(short i, short j, short value) {
	//value = 1 : X      value = 2: O
	if (status->value[i][j] != NULL) {
		char chess;
		if (value == 1) chess = 'X';
		else if (value == 2) chess = 'O';
		status->add(i, j, value);
		DrawChess(i, j, chess);
	}
	else {
		//BAO LOI 
	}
}
void ChessTable::gotoBox(short row, short col) {
	short topX = _LENGTH_HORIZONTAL * col;
	short topY = _LENGTH_VERTICAL * row;
	GotoXY(topX, topY + 1);
}