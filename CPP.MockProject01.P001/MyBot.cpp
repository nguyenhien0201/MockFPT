#include "MyBot.h"

MyBot::MyBot(short level, Matrix* m) {
	m_lever = level; status = m;
	marked.clear();
	analysisStatus();
}
void MyBot::analysisStatus() {
	Position p;
	for (int i = 0; i < status->getRows(); i++) {
		for (int j = 0; j < status->getCols(); j++) {
			if (status->value[i][j] != NULL) {
				p.x = i;
				p.y = j;
				marked.push_back(p);
			}
		}
	}
}
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

void analysis(Matrix* m, short& available) {
	available = 0;
	for (int i = 0; i < m->getRows(); i++) {
		for (int j = 0; j < m->getCols(); j++) {
			if (m->value[i][j] == NULL) {
				available++;
			}
		}
	}
}
void analysis(Matrix* m, short& rMax, short& cMax, short& rMin, short& cMin) {
	rMax = 0; cMax = 0;
	rMin = 0; cMin = 0;
	for (int i = 0; i < m->getRows(); i++) {
		for (int j = 0; j < m->getCols(); j++) {
			if (m->value[i][j] != NULL) {
				rMin = min(rMin, i);
				cMin = min(rMin, j);
				rMax = max(rMax, i);
				cMax = max(cMax, j);
			}
		}
	}

}
//x ,y la toa do diem duoc chon de xu ly, co the la toa do ma human vua nhap
Matrix* MyBot::process(short x, short y) {
	//top left
	m_start.x = x > 0 ? x - 1 : 0;
	m_start.y = y > 0 ? y - 1 : 0;
	//bottom right+1
	m_end.x = x < ROWS - 1 ? x + 1 : ROWS - 1;
	m_end.y = y < COLS - 1 ? y + 1 : COLS - 1;
	//short r_s = x > 0 ? x - 1 : 0;
	//short c_s = y > 0 ? y - 1 : 0;
	//short r_e = x < ROWS - 1 ? x + 1 : ROWS - 1;
	//short c_e = y < COLS - 1 ? y + 1 : COLS - 1;
	Matrix* m = new Matrix(m_end.x - m_start.x + 1, m_end.y - m_start.y + 1);
	for (int i = m_start.x; i <= m_end.x; i++) {
		for (int j = m_start.y; j <= m_end.y; j++) {
			m->add(i - m_start.x, j - m_start.y, status->getValue(i, j));
		}
	}
	return m;
}
void MyBot::easyProcess() {
	short avlb = 0;
	short x = 0, y = 0;
	Matrix* m;
	//tao ma tran con <= 3x3
	m = process(previous.x, previous.y);
	//phan tich xem ma tran m have spot available
	analysis(m, avlb);
	if (avlb == 0) {
		list<Position>::iterator i;
		i = marked.begin();
		do {
			x = i->x;
			y = i->y;
			m = process(x, y);
			analysis(m, avlb);
			if (avlb == 0 && i != marked.end()) i++;
		} while (avlb == 0);
	}

	bestMove(m);
}
void MyBot::normalProcess() {
	easyProcess();
	//delete m;
}
void MyBot::hardProcess() {
	normalProcess();

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