#pragma once
#include "Piece.h"
#include <cctype>
#include <iostream>
#include <math.h>

class Knight : public Piece
{
public:
	Knight(char name);
	~Knight();
	virtual bool IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[], int& result, bool whitePlays, const bool move) override;
};