#include "playboard.h"
#include <iostream>

playboard::playboard()
{
	cell.setSize(Vector2f(38.f, 38.f));
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++) b[i][j] = 0;
	setpiece();
	t = clock();
	drop[0][1] = (active.r1.getPosition().x - 50) / 40;
	drop[0][0] = (active.r1.getPosition().y - 80) / 40;
	drop[1][1] = (active.r2.getPosition().x - 50) / 40;
	drop[1][0] = (active.r2.getPosition().y - 80) / 40;
	drop[2][1] = (active.r3.getPosition().x - 50) / 40;
	drop[2][0] = (active.r3.getPosition().y - 80) / 40;
	drop[3][1] = (active.r4.getPosition().x - 50) / 40;
	drop[3][0] = (active.r4.getPosition().y - 80) / 40;
	holdqueue.setSize(Vector2f(180.f, 100.f));
	nextqueue.setSize(Vector2f(180.f, 500.f));
	holdqueue.setPosition({490, 100});
	nextqueue.setPosition({490, 220});
	holdqueue.setFillColor(Color::Black);
	holdqueue.setOutlineColor(Color::Blue);
	holdqueue.setOutlineThickness(3);
	nextqueue.setFillColor(Color::Black);
	nextqueue.setOutlineColor(Color::Blue);
	nextqueue.setOutlineThickness(3);
}

void playboard::setpiece()
{
	dropped = false;
	if (o.order.size() == 0) o.setup();
	active.create(o.order[0], 210, 40);
	a = 1 + s.find(o.order[0]);
	o.order.erase(0, 1);
	state = 0;
	nextpiece();
}

void playboard::showboard(RenderWindow& w)
{
	if (dropped)
	{
		held = false;
		reset();
		lineclear();
		setpiece();
	}
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
		{
			switch (b[i][j])
			{
			case 0:
				cell.setFillColor(Color(200, 200, 200));
				break;
			case 1:
				cell.setFillColor(Color::Cyan);
				break;
			case 2:
				cell.setFillColor(Color::Yellow);
				break;
			case 3:
				cell.setFillColor(Color::Magenta);
				break;
			case 4:
				cell.setFillColor(Color(255, 128, 0));
				break;
			case 5:
				cell.setFillColor(Color::Blue);
				break;
			case 6:
				cell.setFillColor(Color::Green);
				break;
			case 7:
				cell.setFillColor(Color::Red);
				break;
			}
			cell.setPosition({50 + 40 * j, 80 + 40 * i});
			w.draw(cell);
		}
	levels.showprogress(w);
}

void playboard::findplace(shape a)
{
	drop[0][1] = (a.r1.getPosition().x - 50) / 40;
	drop[0][0] = (a.r1.getPosition().y - 80) / 40;
	drop[1][1] = (a.r2.getPosition().x - 50) / 40;
	drop[1][0] = (a.r2.getPosition().y - 80) / 40;
	drop[2][1] = (a.r3.getPosition().x - 50) / 40;
	drop[2][0] = (a.r3.getPosition().y - 80) / 40;
	drop[3][1] = (a.r4.getPosition().x - 50) / 40;
	drop[3][0] = (a.r4.getPosition().y - 80) / 40;
}

void playboard::reset()
{
	findplace(active);
	for (int i = 0; i < 4; i++)
	{
		if (drop[i][0] < 0)
		{
			playable = false;
			break;
		}
	}
	if (!playable)
	{
		hold.r1.setFillColor(Color::Black);
		hold.r2.setFillColor(Color::Black);
		hold.r3.setFillColor(Color::Black);
		hold.r4.setFillColor(Color::Black);
		hold.s = 0;
		level = 0;
		held = false;
		o.setup();
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 10; j++) b[i][j] = 0;
		setpiece();
		playable = true;
		clearedlines = 0;
		levels.reset();
	}
	else for (int i = 0; i < 4; i++) b[drop[i][0]][drop[i][1]] = a;
	dropped = false;
}

bool playboard::touched(shape a)
{
	findplace(a);
	for (int i = 0; i < 4; i++)
	{
		if (drop[i][0] == 19) return true;
		else if ((drop[i][0] >= 0) && (b[drop[i][0] + 1][drop[i][1]] != 0)) return true;
	}
	return false;
}

bool playboard::lefttouched()
{
	findplace(active);
	for (int i = 0; i < 4; i++)
		if (drop[i][1] == 0) return true;
	for (int i = 0; i < 4; i++)
		if ((drop[i][0] >= 0) && (b[drop[i][0]][drop[i][1] - 1] != 0)) return true;
	return false;
}

bool playboard::righttouched()
{
	findplace(active);
	for (int i = 0; i < 4; i++)
		if (drop[i][1] == 9) return true;
	for (int i = 0; i < 4; i++)
		if ((drop[i][0] >= 0) && b[drop[i][0]][drop[i][1] + 1] != 0) return true;
	return false;
}

void playboard::play(RenderWindow& w)
{
	while (w.isOpen())
	{
		while (const std::optional event = w.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) w.close();
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == Keyboard::Scan::C) holdpiece();
				else if (keyPressed->scancode == Keyboard::Scan::Left) active.moveside(1, lefttouched(), righttouched());
				else if (keyPressed->scancode == Keyboard::Scan::Right) active.moveside(-1, lefttouched(), righttouched());
				else if (keyPressed->scancode == Keyboard::Scan::Up) rotatetest(1);
				else if (keyPressed->scancode == Keyboard::Scan::Down) rotatetest(-1);
				else if (keyPressed->scancode == Keyboard::Scan::Space)
				{
					while (!touched(active))
					{
						active.r1.move({0.f, 40.f});
						active.r2.move({0.f, 40.f});
						active.r3.move({0.f, 40.f});
						active.r4.move({0.f, 40.f});
					}
					dropped = true;
				}
				else if (keyPressed->scancode == Keyboard::Scan::S)
				{
					active.movedown(t, touched(active), dropped, 150 * pow(0.9, level));
				}
			}
		}
		w.clear();
		showboard(w);
		ghostmino();
		ghost.show(w);
		active.show(w);
		active.movedown(t, touched(active), dropped, levels.droptime());
		w.draw(holdqueue);
		w.draw(nextqueue);
		for (int i = 0; i < 5; i++) next[i].show(w);
		if (hold.s) hold.show(w);
		w.display();
	}

	// Event ev;
	// while (w.isOpen())
	// {
	// 	while (w.pollEvent(ev))
	// 	{
	// 		switch (ev.type)
	// 		{
	// 		case Event::Closed:
	// 			w.close();
	// 			break;
	// 		case Event::KeyPressed:
	// 			{
	// 				if (Keyboard::isKeyPressed(Keyboard::C)) holdpiece();
	// 				else if (Keyboard::isKeyPressed(Keyboard::Left)) active.moveside(1, lefttouched(), righttouched());
	// 				else if (Keyboard::isKeyPressed(Keyboard::Right)) active.moveside(-1, lefttouched(), righttouched());
	// 				else if (Keyboard::isKeyPressed(Keyboard::Up)) rotatetest(1);
	// 				else if (Keyboard::isKeyPressed(Keyboard::Down)) rotatetest(-1);
	// 				else if (Keyboard::isKeyPressed(Keyboard::Space))
	// 				{
	// 					while (!touched(active))
	// 					{
	// 						active.r1.move(0.f, 40.f);
	// 						active.r2.move(0.f, 40.f);
	// 						active.r3.move(0.f, 40.f);
	// 						active.r4.move(0.f, 40.f);
	// 					}
	// 					dropped = true;
	// 				}
	// 				else if (Keyboard::isKeyPressed(Keyboard::S))
	// 				{
	// 					active.movedown(t, touched(active), dropped, 150 * pow(0.9, level));
	// 				}
	// 			}
	// 			break;
	// 		}
	// 	}
	// 	w.clear();
	// 	showboard(w);
	// 	ghostmino();
	// 	ghost.show(w);
	// 	active.show(w);
	// 	active.movedown(t, touched(active), dropped, levels.droptime());
	// 	w.draw(holdqueue);
	// 	w.draw(nextqueue);
	// 	for (int i = 0; i < 5; i++) next[i].show(w);
	// 	if (hold.s) hold.show(w);
	// 	w.display();
	// }

}

void playboard::lineclear()
{
	bool cleared = true;
	for (int i = 19; i >= 0; i--)
	{
		for (int j = 0; j <= 9; j++)
		{
			if (b[i][j] == 0)
			{
				cleared = false;
				break;
			}
		}
		if (cleared)
		{
			for (int j = 0; j <= 9; j++) b[i][j] = 0;
			for (int k = i; k > 0; k--)
				for (int j = 0; j <= 9; j++) b[k][j] = b[k - 1][j];
			for (int j = 0; j < 9; j++) b[0][j] = 0;
			i++;
			clearedlines++;
		}
		else cleared = true;
	}
	levels.updatelevel(clearedlines);
}

void playboard::nextpiece()
{
	int j = 0;
	for (int i = 0; i < 5; i++)
	{
		if (j < o.order.length())
		{
			next[i].create(o.order[j], 540, 270 + 100 * i);
			j++;
		}
		else
		{
			j = 0;
			for (int k = i; k < 5; k++)
			{
				next[k].create(o.next[j], 540, 270 + 100 * k);
				j++;
			}
			break;
		}
	}
	hold.useable = true;
}

void playboard::rotatetest(int dir)
{
	active.rotate(a, dir, state);
	bool rotated = false, ok = false;
	findplace(active);
	int k = 0;
	int step;
	if (dir == 1) step = (state + 3) % 4;
	else step = state;
	for (int i = 0; i < 4; i++)
	{
		if ((drop[i][0] > 19) || (drop[i][1] < 0) || (drop[i][1] > 9) || (b[drop[i][0]][drop[i][1]] != 0))
		{
			for (k; k < 4; k++)
			{
				for (int j = 0; j < 4; j++)
				{
					if ((drop[j][0] + dir * wallkick[a - 1][step][k][1] > 19) || (drop[j][1] + dir * wallkick[a - 1][step][k][0] > 9) || (drop[j][1] + dir * wallkick[a - 1][step][k][0] < 0) || (b[drop[j][0] + dir * wallkick[a - 1][step][k][1]][drop[j][1] + dir * wallkick[a - 1][step][k][0]] != 0)) break;
					if (j == 3) ok = true;
				}
				if (ok)
				{
					active.r1.move({40 * dir * wallkick[a - 1][step][k][0], 40 * dir * wallkick[a - 1][step][k][1]});
					active.r2.move({40 * dir * wallkick[a - 1][step][k][0], 40 * dir * wallkick[a - 1][step][k][1]});
					active.r3.move({40 * dir * wallkick[a - 1][step][k][0], 40 * dir * wallkick[a - 1][step][k][1]});
					active.r4.move({40 * dir * wallkick[a - 1][step][k][0], 40 * dir * wallkick[a - 1][step][k][1]});
					rotated = true;
					break;
				}
			}
			if (rotated) break;
		}
		else if (i == 3) rotated = true;
	}
	if (!rotated) active.rotate(a, -dir, state);
}

void playboard::holdpiece()
{
	if (!held)
	{
		a = hold.s;
		state = 0;
		if (hold.s == 0)
		{
			hold.s = active.s;
			setpiece();
		}
		else
		{
			swap(hold.s, active.s);
			active.create(s[active.s - 1], 210, 40);
		}
		hold.create(s[hold.s - 1], 540, 150);
		held = true;
		hold.useable = false;
	}
}

void playboard::ghostmino()
{
	ghost.create(s[a - 1], active.r1.getPosition().x, active.r1.getPosition().y);
	ghost.ghost = true;
	ghost.r1.setFillColor(Color::White);
	ghost.r2.setFillColor(Color::White);
	ghost.r3.setFillColor(Color::White);
	ghost.r4.setFillColor(Color::White);
	g = 0;
	while (g != state)
	{
		ghost.rotate(ghost.s, 1, g);
	}
	if ((ghost.s == 1) && ((state == 1) || (state == 2)))
	{
		ghost.r1.move({-40.f, 0.f});
		ghost.r2.move({-40.f, 0.f});
		ghost.r3.move({-40.f, 0.f});
		ghost.r4.move({-40.f, 0.f});
	}
	while (!touched(ghost))
	{
		ghost.r1.move({0.f, 40.f});
		ghost.r2.move({0.f, 40.f});
		ghost.r3.move({0.f, 40.f});
		ghost.r4.move({0.f, 40.f});
	}
}
