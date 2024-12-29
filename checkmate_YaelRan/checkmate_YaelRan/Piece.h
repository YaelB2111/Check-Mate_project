#pragma once
#include <iostream>
#include <string>

using namespace std;
class Piece
{
public:
	Piece(const string name);
	~Piece();
	void MovePlace(const int destX, const int destY, const int srcX, const int srcY, Piece* board[]);
	bool IsSelfCheck(const int srcX, const int srcY, const Piece* board[], const bool whitePlays);
	void Eat(const int destX, const int destY, const int srcX, int srcY, Piece* board[]);
	virtual bool IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[]) = 0;
private:
	string _name;

};

