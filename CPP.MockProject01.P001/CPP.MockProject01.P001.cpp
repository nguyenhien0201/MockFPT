#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

#include "MyConsole.h"
#include "ChessTable.h"
using namespace std;

void menu(WORD color) {
	SetColor(color);
	cout << "*--------------MAIN MENU------------*" << endl;
	cout << "Press number to choose" << endl;
	cout << "1.Play with other player" << endl;
	cout << "2.Play with BOT" << endl;
	cout << "3.Play with other player" << endl;
	cout << "4.Play with other player" << endl;

}
int main()
{
	menu(2);
	DeleteArea(6, 40, 0, 0);
	SetColor(6);
	//ve ban co tai o 1,1 // o la box
	ChessTable chessTable(1, 1);
	chessTable.display();
	SetColor(12);
	//luu lai vi tri de in ra guild khac
	short x = GetX();
	short y = GetY();
	chessTable.draw(0, 2, 1);
	//chessTable.draw(3, 3, 2);
	chessTable.draw(0, 3, 2);
	chessTable.draw(1, 1, 1);
	chessTable.draw(1, 0, 2);
	chessTable.draw(2, 0, 1);
	chessTable.draw(1, 2, 2);
	chessTable.draw(2, 2, 1);
	chessTable.draw(2, 1, 2);
	chessTable.draw(3, 2, 1);
	chessTable.draw(3, 0, 2);
	GotoXY(x - 1, y + 1);
	cout << chessTable.checkWin(chessTable.status, 3, 0);;
	_getch();
	return 0;
}

