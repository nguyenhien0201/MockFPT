#include "MyBot.h"

//short MyBot::checkStateGame(Matrix* board, Move mov) {
//	ChessTable temp(board->getRows(), board->getCols());
//	return temp.checkWin(mov.x, mov.y);
//}
void MyBot::generateMove() {
	for (short i = 0; i < ROWS; i++) {
		for (short j = 0; j < COLS; j++) {
			if (status->value[i][j] == NULL) {
				m_move = { i,j };
			}
		}
	}
	bestMove();
}
void MyBot::bestMove() {
	int bestScore = -_INFINITY_;
	//m_move = { 0,0 };
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			// Is the spot available?
			if (status->value[i][j] == NULL) {
				status->value[i][j] = ai;
				int score = minimax(status, 0, true);
				status->value[i][j] = NULL;
				if (score > bestScore) {
					bestScore = score;
					m_move.x = i;
					m_move.y = j;
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
	if (rs == 1) return MIN + depth;
	if (rs == DRAW_GAME) return 0;
}
short MyBot::minimax(Matrix* m, short depth, bool isMaximizing) {
	short result = ChessTable::checkWinner(m, m_move.x, m_move.y);
	if (result != NULL) {
		return getScore(result, depth);
	}
	/*else if (depth == m_lever) {
		return 0;
	}*/

	if (isMaximizing) {
		int bestScore = -_INFINITY_;
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				// Is the spot available?
				if (status->value[i][j] == NULL) {
					status->value[i][j] = ai;
					int score = minimax(status, depth + 1, false);
					status->value[i][j] = NULL;
					bestScore = max(score, bestScore);
				}
			}
		}
		return bestScore;
	}
	else {
		int bestScore = _INFINITY_;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// Is the spot available?
				if (status->value[i][j] == NULL) {
					status->value[i][j] = human;
					int score = minimax(status, depth + 1, true);
					status->value[i][j] = NULL;
					bestScore = min(score, bestScore);
				}
			}
		}
		return bestScore;
	}
}