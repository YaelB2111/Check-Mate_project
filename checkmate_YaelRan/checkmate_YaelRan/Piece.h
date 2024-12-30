#pragma once
#include <iostream>
#include <string>
#include <cctype>

using namespace std;
class Piece
{
public:
	Piece(const char name);
	~Piece();
	char GetName() const;
	void MovePlace(const int destX, const int destY, const int srcX, const int srcY, Piece* board[]);
	bool IsSelfCheck(const int srcX, const int srcY, const Piece** board, const bool whitePlays);
	void Eat(const int destX, const int destY, const int srcX, int srcY, Piece** board);
	virtual bool IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece** board, int& result, bool whitePlays) = 0;
private:
	char _name;

};

