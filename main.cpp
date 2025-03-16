#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "playboard.h"

using namespace std;
using namespace sf;

int main()
{
	RenderWindow r(VideoMode({750, 900}), "Tetris", Style::Close | Style::Titlebar);
	playboard p;
	p.play(r);
	return 0;
}

