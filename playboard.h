#pragma once
#include "shape.h"
#include "pieceorder.h"
#include "levels.h"
#include <string>
#include <ctime>
#include <math.h>

class playboard
{
private:
	int b[20][10]{}, drop[4][2]{};
	int highest[10]{};
	RectangleShape cell, holdqueue, nextqueue;
	String s = "iotljsz";
	pieceorder o;
	bool dropped = false, playable = true, held = false;
	const int wallkick[7][4][4][2] = {
		{
		{ {-2, 0}, {1, 0}, {-2, -1}, {1, 2} },
		{ {-1, 0}, {2, 0}, {-1, 2}, {2, -1} },
		{ {2, 0}, {-1, 0}, {2, 1}, {-1, -2} },
		{ {1, 0}, {-2, 0}, {1, -2}, {-2, 1} } },

		{},

		{
		{ {-1, 0}, {-1, -1}, {0, -2}, {-1, -2} },
		{ {1, 0}, {1, -1}, {0, 2}, {1, 2} },
		{ {1, 0}, {1, 1}, {0, -2}, {1, -2} },
		{ {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} } },

		{
		{ {-1, 0}, {-1, -1}, {0, -2}, {-1, -2} },
		{ {1, 0}, {1, -1}, {0, 2}, {1, 2} },
		{ {1, 0}, {1, 1}, {0, -2}, {1, -2} },
		{ {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} } },

		{
		{ {-1, 0}, {-1, -1}, {0, -2}, {-1, -2} },
		{ {1, 0}, {1, -1}, {0, 2}, {1, 2} },
		{ {1, 0}, {1, 1}, {0, -2}, {1, -2} },
		{ {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} } },

		{
		{ {-1, 0}, {-1, -1}, {0, -2}, {-1, -2} },
		{ {1, 0}, {1, -1}, {0, 2}, {1, 2} },
		{ {1, 0}, {1, 1}, {0, -2}, {1, -2} },
		{ {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} } },

		{
		{ {-1, 0}, {-1, -1}, {0, -2}, {-1, -2} },
		{ {1, 0}, {1, -1}, {0, 2}, {1, 2} },
		{ {1, 0}, {1, 1}, {0, -2}, {1, -2} },
		{ {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} } }
	};
	int t, clearedlines = 0, level = 0;
	shape active, next[5], hold, ghost;
	int state = 0, a, g = 0;
	levels levels;
public:
	playboard();
	void showboard(RenderWindow& w);
	void nextpiece();
	void holdpiece();
	void findplace(shape a);
	void reset();
	void setpiece();
	void harddrop(shape a);
	bool touched(shape a);
	bool lefttouched();
	bool righttouched();
	void rotatetest(int dir);
	void lineclear();
	void play(RenderWindow& w);
	void ghostmino();
};