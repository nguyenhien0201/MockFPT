#include<iostream>
#include<string>

using namespace std;
#pragma once
class Player
{
public:
	string name;
	//number of win, number of loss, number of draw
	int now, nol, nod;
	static string ToLower(string s);
	Player();
	Player(Player const &p);
};

