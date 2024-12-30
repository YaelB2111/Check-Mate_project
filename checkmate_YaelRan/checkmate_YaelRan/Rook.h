#pragma once
#include "Piece.h"
#include <cctype>
#include <iostream>

#define VALID_MOVE 0
#define TO_CHECK_MOVE 1
#define NO_PIECE_SRC 2
#define PIECE_DST 3
#define SELF_CHECK 4
#define OUT_OF_BOUND 5
#define INVALID_MOVE 6
#define SRC_DST_EQUAL 7
#define CHECK_MOVE 8

class Rook : public Piece
{
public:
	Rook(char name);
	~Rook();
	virtual bool IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[], int& result, bool whitePlays) override;

};

