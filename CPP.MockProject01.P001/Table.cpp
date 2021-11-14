#include "Table.h"


Table::Table(){
	status = new Matrix();
	display();
}
void Table::display() {
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++) {
			drawBox(i, j);
		}
}

void Table::draw(short i, short j, short value) {
	//value = 1 : X      value = 2: O
	char chess;
	if (value == 1) chess = 'X';
	else if (value == 2) chess = 'O';
	drawChess(i, j, chess);
}