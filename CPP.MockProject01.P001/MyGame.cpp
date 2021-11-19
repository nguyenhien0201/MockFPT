#include "MyGame.h"

MyGame::MyGame() {
	replayGames = new Matrix *[NUMBER_OF_GAME_REPLAY];
	for (int i = 0; i < NUMBER_OF_GAME_REPLAY; i++) {
		replayGames[i] = new Matrix(ROWS, COLS);
	}
	players = new Player[MAX_PLAYERS];
}
void MyGame::Start() {
	mainMenu(_Yellow_);
}
void MyGame::endGame() {

	SetColor(_Yellow_);

	char c;
	do {
		cout << "Press 'c' to continue: "; cin >> c;
	} while (c != 'c');

	mainMenu(_Yellow_);
}

void MyGame::mainMenu(WORD color) {
	DeleteArea(ROWS * 4, 0, 0);

	SetColor(color);

	int c;
	do {
		GotoXY(0, 0);
		cout << "*--------------MAIN MENU------------*" << endl;
		cout << "1.Play with other player" << endl;
		cout << "2.Play with BOT" << endl;
		cout << "3.Replay" << endl;
		cout << "4.Player's Infomation" << endl;
		cout << "5.Guide" << endl;
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
			playerInfo();
			break;
		case 5:
			Guide();
			break;
		case 6:
			system("cls");
			exit(0);
			break;
		}
	} while (c != 6);
}
void MyGame::menuPlayWithBOT(WORD color) {
	DeleteArea(8, 0, 0);
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
			mainMenu(6);
			break;
		}
	} while (c != 4);
}
void MyGame::backMainMenu(bool Clean) {
	char c;
	do {
		cout << "Press 'm' to back MAIN MENU: "; cin >> c;
	} while (c != 'm');

	if (Clean) system("cls");

	mainMenu(_Yellow_);
}

void MyGame::playWithPlayer() {
	replayMoves.clear();
	DeleteArea(8, 0, 0);
	GotoXY(0, 0);

	short turn = 1;
	short x = 0, y = 0;
	short current_point_x, current_point_y;

	Player player1, player2;
	coutWithColor("Name of Player 1: ", _Light_Red_); cin >> player1.name;
	coutWithColor("Name of Player 2: ", _Light_Aqua_); cin >> player2.name;
	DeleteArea(2, 0, 0);

	GotoXY(0, 0);
	coutWithColor("=>" + player1.name + " : X\t", _Light_Red_);
	coutWithColor(player2.name + " : O", _Light_Aqua_);

	SetColor(_Yellow_);

	ChessTable chessTable(2, 1);
	chessTable.display();

	do {

		do {
			GotoBox(ROWS + 3, 0);
			current_point_x = GetX();
			current_point_y = GetY();

			short color = turn == 1 ? _Light_Red_ : _Light_Aqua_;
			string name = turn == 1 ? player1.name : player2.name;
			SetColor(color);
			cout << "Player " << turn << ": " << name << "'s turn: ";
			cin >> x >> y;
			DeleteArea(3, current_point_x, current_point_y);
			SetColor(color);
		} while (!chessTable.checkMove(x, y));

		//SetColor(_Yellow_);
		chessTable.draw(x, y, turn);
		saveMove(x, y);
		turn = turn == 1 ? 2 : 1;
	} while (chessTable.checkWin(x, y) == NULL);

	saveGame(chessTable.status);

	GotoBox(ROWS + 3, 0);
	short winer = chessTable.checkWin(x, y);
	if (winer == DRAW_GAME) {
		player1.nod++; player2.nod++;
		cout << "This match is draw" << endl;
	}
	else {
		short color; string name;
		if (winer == 1) {
			color = _Light_Red_; name = player1.name;
			player1.now++; player2.nol++;
		}
		else {
			color = _Light_Aqua_; name = player2.name;
			player1.nol++; player2.now++;
		}
		SetColor(color);
		cout << "Player " << winer << ": " << name << " win" << endl;
	}
	savePlayerToBuffer(player1);
	savePlayerToBuffer(player2);

	endGame();
}
//thuat toan co van de
void MyGame::playWithBot(short level) {
	replayMoves.clear();
	DeleteArea(8, 0, 0);
	GotoXY(0, 0);

	short turn = 1;
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
				DeleteArea(2, current_point_x, current_point_y);
				current_point_x = x; current_point_y = y; //luu lai de chuyen vao bot
				SetColor(color);
			}
			else {
				MyBot* bot = new MyBot(level, chessTable.status);
				bot->previous.x = current_point_x;
				bot->previous.y = current_point_y;
				bot->generateMove();
				x = bot->m_x;
				y = bot->m_y;
			}

		} while (!chessTable.checkMove(x, y));

		chessTable.draw(x, y, turn);
		saveMove(x, y);
		turn = turn == 1 ? 2 : 1;
	} while (chessTable.checkWin(x, y) == 0);

	saveGame(chessTable.status);

	GotoBox(ROWS + 3, 0);
	short winer = chessTable.checkWin(x, y);
	if (winer == DRAW_GAME) {
		cout << "This match is draw" << endl;
	}
	else {
		short color = winer == 1 ? _Light_Red_ : _Light_Aqua_;
		SetColor(color);
		if (winer == 1) cout << "You are win" << endl;
		else cout << "You are lose" << endl;
	}

	endGame();
}

//void copyMatrix(Matrix* a, Matrix* b) {
//	for (int i = 0; i < ROWS; i++) {
//		for (int j = 0; j < COLS; j++) {
//			a->value[i][j] = b->value[i][j];
//		}
//	}
//}
void MyGame::saveMove(short x, short y) {
	Position m;
	m.x = x; m.y = y;
	replayMoves.push_back(m);
}
void MyGame::saveGame(Matrix* m) {
	for (int i = NUMBER_OF_GAME_REPLAY - 1; i >= 1; i--) {
		Matrix::copyMatrix(replayGames[i], replayGames[i - 1]);
	}
	Matrix::copyMatrix(replayGames[0], m);
}
void MyGame::replay() {
	DeleteArea(ROWS * 5, 0, 0);
	GotoXY(0, 0);
	SetColor(_Yellow_);
	cout << "*---------------------REPLAY AND HISTORY-------------------------*" << endl;
	replayLastGame();
	for (int i = 1; i < NUMBER_OF_GAME_REPLAY; i++) {
		displayHistory(replayGames[i], i);
	}
	SetColor(_Yellow_);
	GotoBox(NUMBER_OF_GAME_REPLAY*(ROWS + 1) + 1, 0);
	backMainMenu(true);
}
void MyGame::replayLastGame() {
	SetColor(_Yellow_);
	ChessTable cb(1, 2);

	cb.display();
	//SetColor(_White_);

	list<Position>::iterator i;
	i = replayMoves.begin();
	bool human = 1;
	//for (int j = 1; i != replayMoves.end() && j <= index * ROWS*COLS; j++) i++;
	while (i != replayMoves.end()) {
		if (human) {
			SetColor(_Light_Red_);
			cb.draw(i->x, i->y, 1);
		}
		else {
			SetColor(_Light_Aqua_);
			cb.draw(i->x, i->y, 2);
		}
		//delay
		Sleep(1000);
		human ^= 1; i++;
	}

}
void MyGame::displayHistory(Matrix* m, int index) {
	SetColor(3 * index + 1);
	ChessTable cb(index * (ROWS + 1) + 1, 2);

	cb.display();
	//SetColor(_White_);
	cb.draw(m);
}

void MyGame::Guide() {
	DeleteArea(9, 0, 0);
	GotoXY(0, 0);
	SetColor(_Yellow_);

	cout << "*----------------HOW TO PLAY--------------*" << endl << endl;
	cout << "1. Lan luot nhap toa do (so _dong so_cot)\n";
	cout << "2. Neu ben nao co " << CONDITION_WIN + 1 << " quan co cua minh giong nhau lien tiep thi se thang\n";
	cout << endl;
	backMainMenu(0);
}

int MyGame::playerCount() {
	int count = 0;
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (players[i].name != "") count++;
	}
	return count;
}

void MyGame::savePlayerToBuffer(Player p) {
	int nop = playerCount();
	if (nop == 0) players[nop] = p;
	else {
		bool exist = false;

		for (int i = 0; i < nop; i++) {
			if (players[i].name == Player::ToLower(p.name)) {
				exist = true;
				players[i].now += p.now;
				players[i].nol += p.nol;
				players[i].nod += p.nod;
				break;
			}
		}
		if (!exist) players[nop] = p;
	}


}

void MyGame::playerInfo() {
	system("cls");
	SetColor(_Yellow_);
	GotoXY(0, 0);

	cout << "*--------------PLAYER INFO------------*" << endl;
	for (int i = 0; i < playerCount(); i++) {
		cout << "Player " << i + 1 << ": " << endl;
		cout << "Name: " << players[i].name << endl;
		cout << "\tWin: " << players[i].now << endl;
		cout << "\tDraw: " << players[i].nod << endl;
		cout << "\tLoss: " << players[i].nol << endl;
		cout << endl;
	}
	backMainMenu(true);
}