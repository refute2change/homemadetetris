#pragma once
#include <string>
#include <ctime>

using namespace std;

class pieceorder
{
private:
	const string s = "iotljsz";
public:
	string order, next;
	pieceorder();
	void setup();
};

