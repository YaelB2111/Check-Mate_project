#pragma once
#include "Piece.h"
#include <cctype>
#include <iostream>
#include <math.h>

class King : public Piece
{
public:
	King(char name);
	~King();
	virtual bool IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[], int& result, bool whitePlays) override;
};

