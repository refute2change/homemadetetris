#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class levels
{
private:
	int level = 1;
	RectangleShape bar, progress;
	const int levelup[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 13, 15, 17, 20, 23, 26, 30, 34, 38, 43 };
public:
	Text* l = nullptr;
	Font f;
	levels();
	const float droptime() const;
	void reset();
	void updatelevel(int& clearedlines);
	void showprogress(RenderWindow& w) const;
};

