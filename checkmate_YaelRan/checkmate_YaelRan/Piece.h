#pragma once
#include <iostream>
#include <string>

using namespace std;
class Piece
{
public:
	Piece(string name);
	~Piece();
	void MovePlace(int destX, int destY, int srcX, int srcY, Piece* board[]);
	bool IsSelfCheck(int srcX, int srcY, Piece* board[], bool whitePlays);
	void Eat(int destX, int destY, int srcX, int srcY, Piece* board[]);
	virtual bool IsMoveLegal(int destX, int destY, int srcX, int srcY, Piece* board[]) = 0;
private:
	string _name;

};

