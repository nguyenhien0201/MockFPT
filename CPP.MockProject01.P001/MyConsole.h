#include <string>
#include <iostream>
#include <windows.h>

#define _LENGTH_HORIZONTAL 4
#define _LENGTH_VERTICAL 2
//MAU
#define _Black_ 0
#define _Blue_ 1
#define _Green_ 2
#define _Aqua_ 3
#define _Red_ 4
#define _Purple_ 5
#define _Yellow_ 6
#define _White_ 7
#define _Gray_ 8
#define _Light_Blue_ 9
#define _Light_Green_ 10
#define _Light_Aqua_ 11
#define _Light_Red_ 12
#define _Light_Purple_ 13
#define _Light_Yellow_ 14
#define _Bright_White_ 15

using namespace std;
/*
. ho tro ve ban co
*/
#pragma once

//doi kich thuoc cua so console
void SetWindowSize(SHORT width, SHORT height);

void SetScreenBufferSize(SHORT width, SHORT height);
//di con tro den vi tri x, y 
void GotoXY(short col, short row);
//tra ve hoanh do con tro console hien tai
short GetX();
//tra ve tung do con tro console hien tai
short GetY();

//doi mau chu
/*
0 = Black	8 = Gray
1 = Blue	9 = Light Blue
2 = Green	10 = Light Green
3 = Aqua	11 = Light Aqua
4 = Red		12 = Light Red
5 = Purple	13 = Light Purple
6 = Yellow	14 = Light Yellow
7 = White	15 = Bright White
*/
void SetColor(WORD color);
//doi mau nen console
void SetBackgroundColor(WORD color);
//ve o co
void DrawBox(short row, short col);
//di den o r,c
void GotoBox(short r, short c);
//ve 1 quan co tai row col
void DrawChess(short row, short col, char chess);

//xoa r hang,c cot bat dau tu toa do topX topY
void DeleteArea(short rows, short cols, short topX, short topY);
void DeleteArea(short rows, short topX, short topY);
void coutWithColor(string input, WORD color);