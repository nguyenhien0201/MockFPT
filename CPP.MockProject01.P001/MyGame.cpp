#include "MyGame.h"

void MyGame::Menu(WORD color) {
	/*SetColor(color);

	int c;

	do {
		cout << "*--------------MAIN MENU------------*" << endl;
		cout << "1.Play with other player" << endl;
		cout << "2.Play with BOT" << endl;
		cout << "3.Replay" << endl;
		cout << "4.Player's Infomation" << endl;
		cout << "5.Guild" << endl;
		cout << "6.Exit" << endl;
		cout << "Press number to choose: "; cin >> c;

		switch (c) {
		case 1:
			playWithPlayer();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		}
	} while (c != 6);*/

	playWithPlayer();
}

void Guild(WORD color) {
	SetColor(color);
	cout << "*--------------HOW TO PLAY------------*" << endl;
}

void menuPlayWithBOT(WORD color) {
	SetColor(color);

	int c;

	do {
		cout << "*--------------PLAY WITH BOT------------*" << endl;
		cout << "1.Easy Mode" << endl;
		cout << "2.Normal Mode" << endl;
		cout << "3.Hard Mode" << endl;
		cout << "4.Back to MAIN MENU" << endl;
		cout << "Press number to choose: "; cin >> c;

		switch (c) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		}
	} while (c != 4);
}

void MyGame::Start() {
	Menu(12);
}

void playWithPlayer() {
	int turn = 1;
	int x = 0, y = 0;

	SetColor(6);
	ChessTable chessTable(1, 1);
	chessTable.display();
	do {
		cout << endl;
		cout << "Player " << turn << "'s turn: "; cin >> x >> y;

		chessTable.draw(x, y, turn);
	} while (chessTable.checkWin(chessTable.status, x, y) == 0);
}