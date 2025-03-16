#include "pieceorder.h"
#include <iostream>

pieceorder::pieceorder()
{
	srand(time(0));
	int t;
	for (int i = 0; i < 7; i++)
	{
		while (1)
		{
			t = rand() % 7;
			if (order.find(s[t]) == string::npos)
			{
				order.push_back(s[t]);
				break;
			}
		}
	}
	for (int i = 0; i < 7; i++)
	{
		while (1)
		{
			t = rand() % 7;
			if (next.find(s[t]) == string::npos)
			{
				next.push_back(s[t]);
				break;
			}
		}
	}
}

void pieceorder::setup()
{
	order = next;
	next = "";
	int t;
	for (int i = 0; i < 7; i++)
	{
		while (1)
		{
			t = rand() % 7;
			if (next.find(s[t]) == string::npos)
			{
				next.push_back(s[t]);
				break;
			}
		}
	}
}