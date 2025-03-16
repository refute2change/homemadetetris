#include "shape.h"
#include <iostream>
using namespace std;

shape::shape()
{
	r1.setSize(Vector2f(38.f, 38.f));
	r2.setSize(Vector2f(38.f, 38.f));
	r3.setSize(Vector2f(38.f, 38.f));
	r4.setSize(Vector2f(38.f, 38.f));
}

void shape::create(char ch, int x, int y)
{
	r1.setPosition({x, y});
	switch (ch)
	{
	case 'i':
		r1.setFillColor(Color::Cyan);
		r2.setFillColor(Color::Cyan);
		r3.setFillColor(Color::Cyan);
		r4.setFillColor(Color::Cyan);
		r2.setPosition({x - 40, y});
		r3.setPosition({x + 40, y});
		r4.setPosition({x + 80, y});
		s = 1;
		break;
	case 'o':
		r1.setFillColor(Color::Yellow);
		r2.setFillColor(Color::Yellow);
		r3.setFillColor(Color::Yellow);
		r4.setFillColor(Color::Yellow);
		r2.setPosition({x + 40, y});
		r3.setPosition({x + 40, y - 40});
		r4.setPosition({x, y - 40});
		s = 2;
		break;
	case 't':
		r1.setFillColor(Color::Magenta);
		r2.setFillColor(Color::Magenta);
		r3.setFillColor(Color::Magenta);
		r4.setFillColor(Color::Magenta);
		r2.setPosition({x - 40, y});
		r3.setPosition({x + 40, y});
		r4.setPosition({x, y - 40});
		s = 3;
		break;
	case 'l':
		r1.setFillColor(Color(255, 128, 0));
		r2.setFillColor(Color(255, 128, 0));
		r3.setFillColor(Color(255, 128, 0));
		r4.setFillColor(Color(255, 128, 0));
		r2.setPosition({x - 40, y});
		r3.setPosition({x + 40, y});
		r4.setPosition({x + 40, y - 40});
		s = 4;
		break;
	case 'j':
		r1.setFillColor(Color::Blue);
		r2.setFillColor(Color::Blue);
		r3.setFillColor(Color::Blue);
		r4.setFillColor(Color::Blue);
		r2.setPosition({x + 40, y});
		r3.setPosition({x - 40, y});
		r4.setPosition({x - 40, y - 40});
		s = 5;
		break;
	case 's':
		r1.setFillColor(Color::Green);
		r2.setFillColor(Color::Green);
		r3.setFillColor(Color::Green);
		r4.setFillColor(Color::Green);
		r2.setPosition({x - 40, y});
		r3.setPosition({x, y - 40});
		r4.setPosition({x + 40, y - 40});
		s = 6;
		break;
	case 'z':
		r1.setFillColor(Color::Red);
		r2.setFillColor(Color::Red);
		r3.setFillColor(Color::Red);
		r4.setFillColor(Color::Red);
		r2.setPosition({x + 40, y});
		r3.setPosition({x, y - 40});
		r4.setPosition({x - 40, y - 40});
		s = 7;
		break;
	}
}

void shape::movedown(int& t, bool touched, bool& stop, int level)
{
	const int droptime = level;
	const int holdtime = droptime / 2;
	if (((clock() - t) >= droptime))
	{
		if (!touched)
		{
			r1.move({0.f, 40.f});
			r2.move({0.f, 40.f});
			r3.move({0.f, 40.f});
			r4.move({0.f, 40.f});
			t = clock();
		}
		else
		{
			if (clock() - t >= holdtime) stop = true;
		}
	}
}

void shape::moveside(int s, bool l, bool r)
{
	if (s == -1)
	{
		if (!r)
		{
			r1.move({40.f, 0.f});
			r2.move({40.f, 0.f});
			r3.move({40.f, 0.f});
			r4.move({40.f, 0.f});
		}
	}
	else
	{
		if (!l)
		{
			r1.move({-40.f, 0.f});
			r2.move({-40.f, 0.f});
			r3.move({-40.f, 0.f});
			r4.move({-40.f, 0.f});
		}
	}
}

void shape::show(RenderWindow& w)
{
	if (!useable)
	{
		r1.setFillColor(Color(127, 127, 127));
		r2.setFillColor(Color(127, 127, 127));
		r3.setFillColor(Color(127, 127, 127));
		r4.setFillColor(Color(127, 127, 127));
	}
	else if (ghost)
	{
		r1.setFillColor(Color::White);
		r2.setFillColor(Color::White);
		r3.setFillColor(Color::White);
		r4.setFillColor(Color::White);
	}
	else switch (s)
	{
	case 1:
		r1.setFillColor(Color::Cyan);
		r2.setFillColor(Color::Cyan);
		r3.setFillColor(Color::Cyan);
		r4.setFillColor(Color::Cyan);
		break;
	case 2:
		r1.setFillColor(Color::Yellow);
		r2.setFillColor(Color::Yellow);
		r3.setFillColor(Color::Yellow);
		r4.setFillColor(Color::Yellow);
		break;
	case 3:
		r1.setFillColor(Color::Magenta);
		r2.setFillColor(Color::Magenta);
		r3.setFillColor(Color::Magenta);
		r4.setFillColor(Color::Magenta);
		break;
	case 4:
		r1.setFillColor(Color(255, 128, 0));
		r2.setFillColor(Color(255, 128, 0));
		r3.setFillColor(Color(255, 128, 0));
		r4.setFillColor(Color(255, 128, 0));
		break;
	case 5:
		r1.setFillColor(Color::Blue);
		r2.setFillColor(Color::Blue);
		r3.setFillColor(Color::Blue);
		r4.setFillColor(Color::Blue);
		break;
	case 6:
		r1.setFillColor(Color::Green);
		r2.setFillColor(Color::Green);
		r3.setFillColor(Color::Green);
		r4.setFillColor(Color::Green);
		break;
	case 7:
		r1.setFillColor(Color::Red);
		r2.setFillColor(Color::Red);
		r3.setFillColor(Color::Red);
		r4.setFillColor(Color::Red);
		break;
	}
	w.draw(r1);
	w.draw(r2);
	w.draw(r3);
	w.draw(r4);
}

void shape::rotate(int piece, int direction, int& state)
{
	if (direction == 1)
	{
		r1.move({rotations[piece - 1][state][0][0], rotations[piece - 1][state][0][1]});
		r2.move({rotations[piece - 1][state][1][0], rotations[piece - 1][state][1][1]});
		r3.move({rotations[piece - 1][state][2][0], rotations[piece - 1][state][2][1]});
		r4.move({rotations[piece - 1][state][3][0], rotations[piece - 1][state][3][1]});
		state = (state + 1) % 4;
	}
	else
	{
		int x = (state + 3) % 4;
		r1.move({-rotations[piece - 1][x][0][0], -rotations[piece - 1][x][0][1]});
		r2.move({-rotations[piece - 1][x][1][0], -rotations[piece - 1][x][1][1]});
		r3.move({-rotations[piece - 1][x][2][0], -rotations[piece - 1][x][2][1]});
		r4.move({-rotations[piece - 1][x][3][0], -rotations[piece - 1][x][3][1]});
		state = (state + 3) % 4;
	}
}
