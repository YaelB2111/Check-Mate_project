#include "Rook.h"

Rook::Rook(char name) : Piece(name)
{
}

Rook::~Rook()
{
}

bool Rook::IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[], int& result, bool whitePlays)
{
	char name = 'r';
	bool legal = false;
	int boardSize = SIZE;

	if (whitePlays) // if white plays then r = R
	{
		name = toupper(name);
	}
	if (name != board[srcX][srcY].GetName()) //  no piece in source or not your team's piece
	{
		result = NO_PIECE_SRC;
		return legal;
	}

	if (whitePlays && board[destX][destY].GetName() != tolower(board[destX][destY].GetName())) // for white, dest piece is also white
	{
		result = PIECE_DST;
		return legal;
	}

	else if (!whitePlays && board[destX][destY].GetName() != toupper(board[destX][destY].GetName())) // for black, dest piece is also black
	{
		result = PIECE_DST;
		return legal;
	}

	if (IsSelfCheck(srcX, srcY, board, whitePlays)) // self check
	{
		result = SELF_CHECK;
		return legal;
	}

	if (destX >= boardSize || srcX >= boardSize || destY >= boardSize || srcY >= boardSize) // dest out of board
	{
		result = OUT_OF_BOUND;
		return legal;
	}

	if (destX != srcX && destY != srcY)  // if piece changed both directions 
	{
		result = INVALID_MOVE;
		return legal;
	}

	//check that there's not piece in the middle of the move
	if (srcY > destY)
	{
		legal = IsLegalBackward(destY, srcX, srcY, board);
	}
	else if (destY > srcY)
	{
		legal = IsLegalForward(destY, srcX, srcY, board);
	}
	else if (srcX > destX)
	{
		legal = IsLegalLeft(destX, srcX, srcY, board);
	}
	else
	{
		legal = IsLegalRight(destX, srcX, srcY, board);
	}
	

	if (!legal)
	{
		result = INVALID_MOVE;
		return legal;
	}

	legal = false;

	if (srcY == destY && srcX == destX) // piece didnt change location
	{
		result = SRC_DST_EQUAL;
		return legal;
	}

	whitePlays = !whitePlays;
	legal = true;
	if (IsSelfCheck(srcX, srcY, board, whitePlays))
	{
		result = TO_CHECK_MOVE;
		return legal;
	}


	result = VALID_MOVE;
	return legal;
}

bool Rook::IsLegalForward(const int destY, const int srcX, const int srcY, const Piece* board[])
{
	int i = 0;
	bool legal = true;

	for (i = srcY; i < destY && !legal; i++)
	{
		if (board[srcX][i].GetName() != '#')
		{
			legal = false;
		}
	}
	return legal;
}


bool Rook::IsLegalBackward(const int destY, const int srcX, const int srcY, const Piece** board)
{
	int i = 0;
	bool legal = true;
	
	for (i = srcY; i > destY && !legal; i--)
	{
		if (board[srcX][i].GetName() != '#')
		{
			legal = false;
		}
	}
	return legal;
}

bool Rook::IsLegalRight(const int destX, const int srcX, const int srcY, const Piece** board)
{
	int i = 0;
	bool legal = true;

	for (i = srcX; i < destX && !legal; i++)
	{
		if (board[i][srcY].GetName() != '#')
		{
			legal = false;
		}
	}
	return legal;
}
bool Rook::IsLegalLeft(const int destX, const int srcX, const int srcY, const Piece** board)
{
	int i = 0;
	bool legal = true;

	for (i = srcX; i > destX && !legal; i--)
	{
		if (board[i][srcY].GetName() != '#')
		{
			legal = false;
		}
	}
	return legal;
}