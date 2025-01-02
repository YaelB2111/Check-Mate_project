#pragma once

#include "Piece.h"
#include <cctype>
#include <iostream>

class Queen : public Piece
{
public:
	Queen(char name);
	~Queen();

	virtual bool IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[], int& result, bool whitePlays) override;
	//rook based funca
	bool IsLegalForward(const int destY, const int srcX, const int srcY, const Piece* board[]);
	bool IsLegalBackward(const int destY, const int srcX, const int srcY, const Piece** board);
	bool IsLegalRight(const int destX, const int srcX, const int srcY, const Piece** board);
	bool IsLegalLeft(const int destX, const int srcX, const int srcY, const Piece** board);

	//bishop based funcs
	bool MoveRightTop(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[]) const;
	bool MoveRightBot(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[]) const;
	bool MoveLeftTop(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[]) const;
	bool MoveLeftBot(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[]) const;
};

