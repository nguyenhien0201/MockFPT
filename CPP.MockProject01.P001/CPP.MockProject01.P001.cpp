#include <iostream>
#include <string>
#include <Windows.h>
#include "MyConsole.h"
#include <stdlib.h>
#include <conio.h>
#include "Table.h"

using namespace std;
void menu() {
	cout << "*--------------MAIN MENU------------*" << endl;
	cout << "Press number to choose" << endl;
	cout << "1.Play with other player" << endl;
	cout << "2.Play with BOT" << endl;
	cout << "3.Play with other player" << endl;
	cout << "4.Play with other player" << endl;

}
int main()
{
	menu();

	Table chessTable;
	chessTable.draw(3, 3, 1);
	chessTable.draw(3, 3, 2);
	
	_getch();
	return 0;
}

