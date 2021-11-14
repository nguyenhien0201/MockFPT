#include <string.h>
#include <iostream>
#include <windows.h>
#define _LENGTH_HORIZONTAL 4
#define _LENGTH_VERTICAL 2

using namespace std;
/*
. ho tro ve ban co
*/
#pragma once

//doi kich thuoc cua so console
void SetWindowSize(SHORT width, SHORT height);

//kich thuoc man hinh dem
void SetScreenBufferSize(SHORT width, SHORT height);
//di con tro den vi tri x, y // go to cot x dong y
void gotoXY(short col, short row);
//tra ve hoanh do con tro console hien tai
int getX();
//tra ve tung do con tro console hien tai
int getY();

//doi mau chu
void setColor(WORD color);
//doi mau nen console
void setBackgroundColor(WORD color);
//ve o co
void drawBox(int row, int col);
//ve 1 quan co tai row col
void drawChess(int row, int col, char chess);

