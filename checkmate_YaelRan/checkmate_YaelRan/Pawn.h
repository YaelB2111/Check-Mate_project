#pragma once

#include "Piece.h"
#include <cctype>
#include <iostream>

class Pawn : public Piece
{
public:
	Pawn(char name);
	~Pawn();
	virtual bool IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[], int& result, bool whitePlays) override;
};

