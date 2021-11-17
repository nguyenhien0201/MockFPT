#include "MyBot.h"

//short MyBot::checkStateGame(Matrix* board, Move mov) {
//	ChessTable temp(board->getRows(), board->getCols());
//	return temp.checkWin(mov.x, mov.y);
//}
//void MyBot::generateMove() {
//	for (short i = 0; i < ROWS; i++) {
//		for (short j = 0; j < COLS; j++) {
//			if (status->value[i][j] == NULL) {
//				m_x = i;
//				m_y = j;
//			}
//		}
//	}
//	bestMove();
//}
void MyBot::bestMove() {
	int bestScore = -_INFINITY_;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			// Is the spot available?
			if (status->value[i][j] == NULL) {
				status->value[i][j] = ai;

				int score = minimax(status, 0, false, i, j);

				status->value[i][j] = NULL;

				if (bestScore < score) {
					bestScore = score;
					m_x = i;
					m_y = j;
				}
			}
		}
	}
	//status->value[m_move.x][m_move.y] = ai;
	//currentPlayerIsHuman = true;
}
int getScore(short rs, short depth) {
	if (rs == ai) {
		return MAX - depth;
	}
	if (rs == human) return MIN + depth;
	if (rs == DRAW_GAME) return 0;
}
short MyBot::minimax(Matrix* m, short depth, bool isMaximizing, short x, short y) {
	//m->display();
	short result = ChessTable::checkWinner(m, x, y);
	if (result != NULL) {
		return getScore(result, depth);
	}
	else if (depth == m_lever) {
		return 0;
	}

	if (isMaximizing) {
		int bestScore = -_INFINITY_;
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				// Is the spot available?
				if (status->value[i][j] == NULL) {
					status->value[i][j] = ai;

					int score = minimax(status, depth + 1, false, i, j);

					status->value[i][j] = NULL;
					bestScore = max(score, bestScore);
				}
			}
		}
		//cout << "BestMax: " << bestScore << endl;
		return bestScore;
	}
	else {
		int bestScore = _INFINITY_;
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				// Is the spot available?
				if (status->value[i][j] == NULL) {
					status->value[i][j] = human;

					int score = minimax(status, depth + 1, true, i, j);

					status->value[i][j] = NULL;
					bestScore = min(score, bestScore);
				}
			}
		}
		//cout << "BestMin: " << bestScore << endl;
		return bestScore;
	}
}