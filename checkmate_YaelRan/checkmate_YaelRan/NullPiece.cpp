#include "NullPiece.h"

NullPiece::~NullPiece()
{
}

NullPiece::NullPiece() : Piece('#')
{
}

bool NullPiece::IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece*** board, int& result, bool whitePlays, bool move)
{
	result = NO_PIECE_SRC;
	return false;
}

