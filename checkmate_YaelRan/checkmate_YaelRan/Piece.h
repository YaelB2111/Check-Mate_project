#pragma once
#include <iostream>
using namespace std;
class Piece
{
public:
	void MovePlace(int destX, int destY, int srcX, int srcY);
	bool IsSelfCheck(int srcX, int srcY);
	void Eat(int destX, int destY, int srcX, int srcY);
	bool IsMoveLegal(int destX, int destY, int srcX, int srcY);
private:
	string _name;

};

