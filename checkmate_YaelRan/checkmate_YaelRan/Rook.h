#pragma once
#include "Piece.h"
#include <cctype>
#include <iostream>


class Rook : public Piece
{
public:
	Rook(char name);
	~Rook();
	virtual bool IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[], int& result, bool whitePlays, const bool move) override;
	bool IsLegalForward(const int destY, const int srcX, const int srcY, const Piece** board[]);
	bool IsLegalBackward(const int destY, const int srcX, const int srcY, const Piece*** board);
	bool IsLegalRight(const int destX, const int srcX, const int srcY, const Piece*** board);
	bool IsLegalLeft(const int destX, const int srcX, const int srcY, const Piece*** board);
};

