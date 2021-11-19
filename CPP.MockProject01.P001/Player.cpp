#include "Player.h"
string Player::ToLower(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] <= 'Z' && s[i] >= 'A')
			s[i] -= ('Z' - 'z');
	}
	return s;
}
Player::Player() {
	name = "";
	now = nol = nod = 0;
}

Player::Player(Player const& p) {
	name = ToLower(p.name);
	now = p.now;
	nol = p.nol;
	nod = p.nod;
}