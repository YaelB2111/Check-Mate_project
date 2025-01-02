#pragma once
#include "Piece.h"
using namespace std;

class NullPiece : public Piece
{
public:
	~NullPiece();
	NullPiece();
<<<<<<< HEAD
	//void GotEaten(const Piece& piece, const Piece** board);
=======
	virtual bool IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece** board, int& result, bool whitePlays) override;
>>>>>>> 4aafe1866398a4ca03bbfc1a4f4a22905e49e6a6
};

