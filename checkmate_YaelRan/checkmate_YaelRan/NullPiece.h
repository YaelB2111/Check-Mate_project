#pragma once
#include "Piece.h"
using namespace std;

class NullPiece : public Piece
{
public:
	~NullPiece();
	NullPiece();
	//void GotEaten(const Piece& piece, const Piece** board);
	virtual bool IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece*** board, int& result, bool whitePlays) override;
};

