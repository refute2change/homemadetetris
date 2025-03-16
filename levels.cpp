#include "levels.h"
#include <math.h>
#include <string>
#include <iostream>

levels::levels()
{
	f.openFromFile("Fonts/arial.ttf");
	l = new Text(f);
	l->setPosition({500, 753});
	l->setFillColor(Color::Black);
	l->setCharacterSize(30);
	l->setString("Level 1");
	bar.setPosition({490, 750});
	bar.setSize(Vector2f(180.f, 50.f));
	bar.setOutlineThickness(3);
	bar.setOutlineColor(Color::Blue);
	bar.setFillColor(Color::Black);
	progress.setFillColor(Color::Red);
	progress.setPosition({493, 753});
	progress.setSize(Vector2f(0.f, 44.f));
}

const float levels::droptime() const
{
	if (level > 25) return 400 * pow(1 - 24 * 0.007, 24);
	else return 400 * pow(1 - (level - 1) * 0.007, level - 1);
}

void levels::reset()
{
	level = 1;
}

void levels::updatelevel(int& clearedlines)
{
	int threshold = 5, i = 1;
	while (clearedlines != 0)
	{
		if (level < levelup[i])
		{
			if (clearedlines >= (levelup[i] - levelup[i - 1]) * (5 * i))
			{
				clearedlines -= (levelup[i] - levelup[i - 1]) * (5 * i);
				level = levelup[i];
				i++;
			}
			else
			{
				level += clearedlines / (5 * i);
				clearedlines %= (5 * i);
				break;
			}
		}
		else i++;
	}
	std::string s = "Level " + std::to_string(level);
	l->setString(s);
	progress.setSize(Vector2f(clearedlines * 174.f / (5 * i), 44.f));
}

void levels::showprogress(RenderWindow& w) const
{
	w.draw(bar);
	w.draw(progress);
	w.draw(*l);
}
