#include "Table.h"


Table::Table(){
	status = new Matrix();
	display();
}
void Table::display() {
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++) {
			DrawBox(i+1, j+1);
		}
}

void Table::draw(short i, short j, short value) {
	//value = 1 : X      value = 2: O
	char chess;
	if (value == 1) chess = 'X';
	else if (value == 2) chess = 'O';
	DrawChess(i, j, chess);
}