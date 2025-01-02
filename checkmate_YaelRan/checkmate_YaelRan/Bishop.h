#pragma once
#include "Piece.h"
#include <cctype>
#include <iostream>


class Bishop : public Piece
{
public:
	Bishop(char name);
	~Bishop();
	virtual bool IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[], int& result, bool whitePlays) override;
	bool MoveRightTop(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[]) const;
	bool MoveRightBot(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[]) const;
	bool MoveLeftTop(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[]) const;
	bool MoveLeftBot(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[]) const;

};


