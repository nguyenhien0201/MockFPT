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
	gotoChessBox(ROWS, m_Y - 1);
}
bool ChessTable::checkMove(short i, short j) {
	//khong ton tai o (i,j) hoac da dien roi
	if ((status->getValue(i, j) == _ERROR_) || status->getValue(i, j)) return false;
	return true;
}

void ChessTable::draw(short i, short j, short value) {
	//value = 1 : X      value = 2: O
	short mark = status->getValue(i, j);
	if (mark == NULL) {
		char chess = value == 1 ? 'X' : value == 2 ? 'O' : 'E';
		status->add(i, j, value);
		DrawChess(i + m_X, j + m_Y, chess);
		//ve thanh cong
	}
}
void ChessTable::draw(Matrix* m) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (m->value[i][j] != NULL)
				draw(i, j, m->value[i][j]);
		}
	}
}
void ChessTable::gotoChessBox(short row, short col) {
	short topX = _LENGTH_HORIZONTAL * (col + m_Y);
	short topY = _LENGTH_VERTICAL * (row + m_X);
	GotoXY(topX + _LENGTH_HORIZONTAL / 2, topY + 1);
}


// 1: player 1; 2:player 2; 0: chua co ai thang
//Kiem tra ai thang
int playerWin(int count, short v) {
	if (count == CONDITION_WIN) return v;
	else return 0;
}

//Kiem tra thang theo hang
int horizontalWin(Matrix* m, int x, int y) {
	//left count, right count
	int count = 0;
	int v = m->value[x][y];
	for (int j = y + 1; j < COLS; j++) {
		if (m->value[x][j] == v) count++;
		else break;
	}

	for (int j = y - 1; j >= 0; j--) {
		if (m->value[x][j] == v) count++;
		else break;
	}
	return playerWin(count, m->value[x][y]);
	//return playerWin(rcount + lcount, m->value[x][y]);
}

//Kiem tra thang theo cot
int verticalWin(Matrix* m, int x, int y) {
	//up count, down count
	int count = 0;

	for (int i = x + 1; i < ROWS; i++) {
		if (m->value[i][y] == m->value[x][y]) count++;
		else break;
	}

	for (int i = x - 1; i >= 0; i--) {
		if (m->value[i][y] == m->value[x][y]) count++;
		else break;
	}

	return playerWin(count, m->value[x][y]);
}

//Kiem tra thang theo duong cheo chinh
int mDiagonalWin(Matrix* m, int x, int y) {
	int count = 0;
	for (int i = x + 1; i < ROWS; i++) {
		for (int j = y + 1; j < COLS; j++) {
			if (j - y == i - x) {
				if (m->value[i][j] == m->value[x][y]) count++;
				else break;
			}
			else continue;
		}
	}

	for (int i = x - 1; i >= 0; i--) {
		for (int j = y - 1; j >= 0; j--) {
			if (y - j == x - i) {
				if (m->value[i][j] == m->value[x][y]) count++;
				else break;
			}
			else continue;
		}
	}
	return playerWin(count, m->value[x][y]);
}

//Kiem tra thang theo duong cheo phu
int aDiagonalWin(Matrix* m, int x, int y) {
	//right up, left down
	int count = 0;

	for (int i = x + 1; i < ROWS; i++) {
		for (int j = y - 1; j >= 0; j--) {
			if (y - j == i - x) {
				if (m->value[i][j] == m->value[x][y]) count++;
				else break;
			}
			else continue;
		}
	}

	for (int i = x - 1; i >= 0; i--) {
		for (int j = y + 1; j < COLS; j++) {
			if (j - y == x - i) {
				if (m->value[i][j] == m->value[x][y]) count++;
				else break;
			}
			else continue;
		}
	}

	return playerWin(count, m->value[x][y]);
}


bool isFull(Matrix* m) {
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++) {
			if (m->value[i][j] == NULL) return false;
		}
	return true;
}
short ChessTable::checkWinner(Matrix* m, short x, short y) {
	int hw = horizontalWin(m, x, y);
	int vw = verticalWin(m, x, y);
	int mdw = mDiagonalWin(m, x, y);
	int adw = aDiagonalWin(m, x, y);
	
	if (isFull(m) && hw == 0 && vw == 0 && mdw == 0 && adw == 0) {
		return DRAW_GAME;
	}
	if (hw) return hw;
	if (vw) return vw;
	if (mdw) return mdw;
	if (adw) return adw;
	//van hoa
	return 0;
}
int ChessTable::checkWin(int x, int y) {
	return checkWinner(status, x, y);
}
