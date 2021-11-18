#include "MyGame.h"

MyGame::MyGame() {
	replayGames = new Matrix *[NUMBER_OF_GAME_REPLAY];
	for (int i = 0; i < NUMBER_OF_GAME_REPLAY; i++) {
		replayGames[i] = new Matrix(ROWS, COLS);
	}
}

void MyGame::Menu(WORD color) {
	DeleteArea(35, 75, 0, 0);

	SetColor(color);

	int c;
	do {
		GotoXY(0, 0);
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
			menuPlayWithBOT(color);
			break;
		case 3:
			replay();
			break;
		case 4:
			break;
		case 5:
			Guild();
			break;
		case 6:
			system("cls");
			exit(0);
			break;
		}
	} while (c != 6);
}

void MyGame::menuPlayWithBOT(WORD color) {
	DeleteArea(8, 50, 0, 0);
	GotoXY(0, 0);

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
			playWithBot(_EASY_);
			break;
		case 2:
			playWithBot(_NORMAL_);
			break;
		case 3:
			playWithBot(_HARD_);
			break;
		case 4:
			Menu(6);
			break;
		}
	} while (c != 4);
}

void MyGame::Start() {
	Menu(_Yellow_);
}

void MyGame::playWithPlayer() {
	DeleteArea(8, 50, 0, 0);
	GotoXY(0, 0);

	int turn = 1;
	short x = 0, y = 0;
	short current_point_x, current_point_y;

	coutWithColor("=> Player 1 = X\t", _Light_Red_);
	coutWithColor("Player 2 = O", _Light_Aqua_);

	SetColor(_Yellow_);

	ChessTable chessTable(2, 1);
	chessTable.display();

	do {

		do {
			GotoBox(ROWS + 3, 0);
			current_point_x = GetX();
			current_point_y = GetY();

			short color = turn == 1 ? _Light_Red_ : _Light_Aqua_;
			SetColor(color);
			cout << "Player " << turn << "'s turn: ";
			cin >> x >> y;
			DeleteArea(2, 30, current_point_x, current_point_y);
			SetColor(color);
		} while (!chessTable.checkMove(x, y));

		//SetColor(_Yellow_);
		chessTable.draw(x, y, turn);

		turn = turn == 1 ? 2 : 1;
	} while (chessTable.checkWin(x, y) == NULL);

	saveGame(chessTable.status);

	//DeleteArea(50, 50, 0, 0);
	//GotoXY(0, 0);
	GotoBox(ROWS + 3, 0);
	short winer = chessTable.checkWin(x, y);
	if (winer == DRAW_GAME) {
		cout << "This match is a draw" << endl;
	}
	else {
		short color = winer == 1 ? _Light_Red_ : _Light_Aqua_;
		SetColor(color);

		cout << "Player " << winer << " win" << endl;
	}

	SetColor(_Yellow_);

	char c;
	do {
		cout << "Press 'c' to continue: "; cin >> c;
	} while (c != 'c');

	Menu(_Yellow_);
}
//thuat toan co van de
void MyGame::playWithBot(short level) {
	DeleteArea(8, 50, 0, 0);
	GotoXY(0, 0);

	int turn = 1;
	short x = 0, y = 0;
	short current_point_x, current_point_y;

	coutWithColor("=> Human = X\t", _Light_Red_);
	coutWithColor("Computer = O", _Light_Aqua_);

	SetColor(_Yellow_);

	ChessTable chessTable(2, 1);
	chessTable.display();

	do {

		do {
			short color = turn == 1 ? _Light_Red_ : _Light_Aqua_;
			SetColor(color);

			if (turn == 1) {
				GotoBox(ROWS + 3, 0);
				current_point_x = GetX();
				current_point_y = GetY();
				cout << "Human's turn: ";
				cin >> x >> y;
				DeleteArea(2, 30, current_point_x, current_point_y);
				SetColor(color);
			}
			else {
				MyBot* bot = new MyBot(level, chessTable.status);
				bot->bestMove();
				x = bot->m_x;
				y = bot->m_y;
			}

		} while (!chessTable.checkMove(x, y));

		chessTable.draw(x, y, turn);

		turn = turn == 1 ? 2 : 1;
	} while (chessTable.checkWin(x, y) == 0);

	saveGame(chessTable.status);

	//DeleteArea(50, 50, 0, 0);
	//GotoXY(0, 0);
	GotoBox(ROWS + 3, 0);
	short winer = chessTable.checkWin(x, y);
	if (winer == DRAW_GAME) {
		cout << "This match is a draw" << endl;
	}
	else {
		short color = winer == 1 ? _Light_Red_ : _Light_Aqua_;
		SetColor(color);

		if (winer == 1) {
			cout << "You are win" << endl;
		}
		else
		{
			cout << "You are lose" << endl;
		}

	}

	SetColor(_Yellow_);

	char c;
	do {
		cout << "Press 'c' to continue: "; cin >> c;
	} while (c != 'c');

	Menu(_Yellow_);
}
void copyMatrix(Matrix* a, Matrix* b) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			a->value[i][j] = b->value[i][j];
		}
	}
}

void MyGame::saveGame(Matrix* m) {
	for (int i = NUMBER_OF_GAME_REPLAY - 1; i >= 1; i--) {
		copyMatrix(replayGames[i], replayGames[i - 1]);
	}
	copyMatrix(replayGames[0], m);
}

void MyGame::replay() {
	DeleteArea(50, 50, 0, 0);
	GotoXY(0, 0);

	SetColor(_Yellow_);
	cout << "*---------------------REPLAY-------------------------*" << endl;

	for (int i = 0; i < NUMBER_OF_GAME_REPLAY; i++) {
		displayOldGame(replayGames[i], i);
	}
}

void MyGame::displayOldGame(Matrix* m, int index) {
	SetColor(3 * index + 1);
	ChessTable cb(index * (ROWS + 1) + 1, 2);

	cb.display();
	SetColor(_White_);
	cb.draw(m);

	if (index == NUMBER_OF_GAME_REPLAY - 1) {
		SetColor(_Yellow_);
		GotoBox(NUMBER_OF_GAME_REPLAY*(ROWS + 1) + 1, 0);
		char c;
		do {
			cout << "Press 'm' to back MAIN MENU: "; cin >> c;
		} while (c != 'm');
		//DeleteArea(40, 135, 0, 0);
		system("cls");

		Menu(_Yellow_);
	}
}

void MyGame::Guild() {
	DeleteArea(9, 50, 0, 0);
	GotoXY(0, 0);
	SetColor(_Yellow_);

	cout << "*----------------HOW TO PLAY--------------*" << endl << endl;
	cout << "1. Lan luot nhap toa do (so _dong so_cot)\n";
	cout << "2. Neu ben nao co " << CONDITION_WIN + 1 << " quan co cua minh giong nhau lien tiep thi se thang\n";
	cout << endl;
	char c;
	do {
		cout << "Press 'm' to back MAIN MENU: "; cin >> c;
	} while (c != 'm');
	Menu(_Yellow_);
}