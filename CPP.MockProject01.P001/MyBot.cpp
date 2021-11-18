#include "MyBot.h"


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

void MyBot::generateMove() {
	if (ROWS == 3) bestMove(status);
	else if (m_lever == _EASY_) {
		easyProcess();
		m_x += m_start.x;
		m_y += m_start.y;
	}
	else if (m_lever == _NORMAL_) {
		normalProcess();
		m_x += m_start.x;
		m_y += m_start.y;
	}
	else if (m_lever == _HARD_) {
		hardProcess();
		m_x += m_start.x;
		m_y += m_start.y;
	}

}

void MyBot::analysis(Matrix* m, short& available) {
	available = 0;
	for (int i = 0; i < m->getRows(); i++) {
		for (int j = 0; j < m->getCols(); j++) {
			if (status->value[i][j] != NULL) {
				available++;
				break;
			}
		}
	}

}

Matrix* MyBot::process(short x, short y) {
	m_start.x = x > 0 ? x - 1 : 0;
	m_start.y = x > 0 ? x - 1 : 0;

	m_end.x = x < ROWS - 1 ? x + 2 : ROWS;
	m_end.y = y < COLS - 1 ? y + 2 : COLS;
	//short r_s = x > 0 ? x - 1 : 0;
	//short c_s = y > 0 ? y - 1 : 0;

	//short r_e = x < ROWS - 1 ? x + 1 : ROWS - 1;
	//short c_e = y < COLS - 1 ? y + 1 : COLS - 1;
	Matrix* m = new Matrix(m_end.x - m_start.x, m_end.y - m_start.y);
	for (int i = m_start.x; i < m_end.x; i++) {
		for (int j = m_start.y; j < m_end.y; j++) {
			m->add(i - m_start.x, j - m_start.y, status->getValue(i, j));
		}
	}
	return m;
}
void MyBot::easyProcess() {
	//short prio, avlb;
	//analysis(prio, avlb);
	/*short r_s = previous.x > 0 ? previous.x - 1 : 0;
	short c_s = previous.y > 0 ? previous.y - 1 : 0;

	short r_e = previous.x < ROWS - 1 ? previous.x + 1 : ROWS - 1;
	short c_e = previous.y < COLS - 1 ? previous.y + 1 : COLS - 1;
	Matrix* m = new Matrix(r_e - r_s + 1, c_e - c_s + 1);
	for (int i = r_s; i <= r_e; i++) {
		for (int j = c_s; j <= c_e; j++) {
			m->add(i - r_s, j - c_s, status->getValue(i, j));
		}
	}*/

	short avlb = 0;
	short i = 0, j = 0;
	Matrix* m;
	m = process(previous.x, previous.y);
	do {

		analysis(m, avlb);
		if (avlb == 0) {
			while (i < status->getRows() && j < status->getCols()) {
				if (status->getValue(i, j) != NULL) {
					break;
				}
				i++;
				j++;
			}
			m = process(i, j);
		}

	} while (avlb == 0);

	bestMove(m);

}
void MyBot::normalProcess() {
	easyProcess();
	//analysis(prio, avlb);


}
void MyBot::hardProcess() {
	easyProcess();
	//analysis(prio, avlb);


}


void MyBot::bestMove(Matrix* m) {
	int bestScore = -_INFINITY_;

	for (int i = 0; i < m->getRows(); i++) {
		for (int j = 0; j < m->getCols(); j++) {
			// Is the spot available?
			if (m->value[i][j] == NULL) {
				m->value[i][j] = ai;

				int score = minimax(m, 0, false, i, j);
				//int score = negamax(status, 0, i, j);
				m->value[i][j] = NULL;

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
	short result = ChessTable::checkWinner(m, x, y, m_winCondition);
	if (result != NULL) {
		return getScore(result, depth);
	}
	else if (depth == m_lever) {
		return 0;
	}

	if (isMaximizing) {
		int bestScore = -_INFINITY_;
		for (int i = 0; i < m->getRows(); i++) {
			for (int j = 0; j < m->getCols(); j++) {
				// Is the spot available?
				if (m->value[i][j] == NULL) {
					m->value[i][j] = ai;

					int score = minimax(m, depth + 1, false, i, j);

					m->value[i][j] = NULL;
					bestScore = max(score, bestScore);
				}
			}
		}
		//cout << "BestMax: " << bestScore << endl;
		return bestScore;
	}
	else {
		int bestScore = _INFINITY_;
		for (int i = 0; i < m->getRows(); i++) {
			for (int j = 0; j < m->getCols(); j++) {
				// Is the spot available?
				if (m->value[i][j] == NULL) {
					m->value[i][j] = human;

					int score = minimax(m, depth + 1, true, i, j);

					m->value[i][j] = NULL;
					bestScore = min(score, bestScore);
				}
			}
		}
		//cout << "BestMin: " << bestScore << endl;
		return bestScore;
	}
}