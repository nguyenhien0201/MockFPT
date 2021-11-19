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
			if (m->value[i][j] != NULL) {
				short color = m->value[i][j] == 1 ? _Light_Red_ : _Light_Aqua_;
				SetColor(color);
				draw(i, j, m->value[i][j]);
			}
		}
	}
}
void ChessTable::gotoChessBox(short row, short col) {
	short topX = _LENGTH_HORIZONTAL * (col + m_Y);
	short topY = _LENGTH_VERTICAL * (row + m_X);
	GotoXY(topX + _LENGTH_HORIZONTAL / 2, topY + 1);
}


// 1: player 1; 2:player 2; 0: chua co ai thang; DRAW_GAME: hoa
//Kiem tra ai thang
int playerWin(int count, short v, short winCondition) {
	if (count == winCondition) return v;
	else return 0;
}

//Kiem tra thang theo hang
int horizontalWin(Matrix* m, int x, int y, short winCondition) {
	//left count, right count
	int count = 0;
	int v = m->value[x][y];
	for (int j = y + 1; j < m->getCols(); j++) {
		if (m->value[x][j] == v) count++;
		else break;
	}

	for (int j = y - 1; j >= 0; j--) {
		if (m->value[x][j] == v) count++;
		else break;
	}
	return playerWin(count, m->value[x][y], winCondition);
	//return playerWin(rcount + lcount, m->value[x][y]);
}

//Kiem tra thang theo cot
int verticalWin(Matrix* m, int x, int y, short winCondition) {
	//up count, down count
	int count = 0;

	for (int i = x + 1; i < m->getRows(); i++) {
		if (m->value[i][y] == m->value[x][y]) count++;
		else break;
	}

	for (int i = x - 1; i >= 0; i--) {
		if (m->value[i][y] == m->value[x][y]) count++;
		else break;
	}

	return playerWin(count, m->value[x][y], winCondition);
}

//Kiem tra thang theo duong cheo chinh
int mDiagonalWin(Matrix* m, int x, int y, short winCondition) {
	int count = 0;
	int i = x + 1, j = y + 1;
	while (i < m->getRows() && j < m->getCols() && m->value[i][j] == m->value[x][y]) {
		count++;
		i++;
		j++;
	}
	i = x - 1; j = y - 1;
	while (i >= 0 && j >= 0 && m->value[i][j] == m->value[x][y]) {
		count++;
		i--;
		j--;
	}
	return playerWin(count, m->value[x][y], winCondition);
}

//Kiem tra thang theo duong cheo phu
int aDiagonalWin(Matrix* m, int x, int y, short winCondition) {
	int count = 0;
	int i = x + 1, j = y - 1;
	while (i < m->getRows() && j >= 0 && m->value[i][j] == m->value[x][y]) {
		count++;
		i++;
		j--;
	}
	i = x - 1, j = y + 1;
	while (i >= 0 && j < m->getCols() && m->value[i][j] == m->value[x][y]) {
		count++;
		i--;
		j++;
	}
	return playerWin(count, m->value[x][y], winCondition);
}

bool isFull(Matrix* m) {
	for (int i = 0; i < m->getRows(); i++)
		for (int j = 0; j < m->getCols(); j++) {
			if (m->value[i][j] == NULL) return false;
		}
	return true;
}
short ChessTable::checkWinner(Matrix* m, short x, short y, short winCondition) {
	int hw = horizontalWin(m, x, y, winCondition);
	int vw = verticalWin(m, x, y, winCondition);
	int mdw = mDiagonalWin(m, x, y, winCondition);
	int adw = aDiagonalWin(m, x, y, winCondition);

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
short ChessTable::checkWin(int x, int y) {
	return checkWinner(status, x, y, CONDITION_WIN);
}
