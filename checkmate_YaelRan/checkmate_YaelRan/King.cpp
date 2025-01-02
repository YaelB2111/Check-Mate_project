#include "King.h"

King::King(char name) : Piece (name)
{
}

King::~King()
{
}

bool King::IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[], int& result, bool whitePlays)
{
	char name = 'k';
	bool legal = false;
	int boardSize = SIZE;

	if (whitePlays) // for white K
	{
		name = toupper(name);
	}

	if (name != board[srcX][srcY]->GetName()) // no piece in source or not right team
	{
		result = NO_PIECE_SRC;
		return legal;
	}

	if (whitePlays && board[destX][destY]->GetName() != tolower(board[destX][destY]->GetName()))// if white eats white
	{
		result = PIECE_DST;
		return legal;
	}

	else if (!whitePlays && board[destX][destY]->GetName() != toupper(board[destX][destY]->GetName())) // if black eats black
	{
		result = PIECE_DST;
		return legal;
	}

	if (IsSelfCheck(srcX, srcY, board, whitePlays))//self check
	{
		result = SELF_CHECK;
		return legal;
	}

	if (destX >= boardSize || srcX >= boardSize || destY >= boardSize || srcY >= boardSize)//out of board
	{
		result = OUT_OF_BOUND;
		return legal;
	}


	if (abs(destX - srcX) > 1 || abs(destY - srcY) > 1) // lings move can change cordinate up to one
	{
		result = INVALID_MOVE;
		return legal;
	}


	if (srcY == destY && srcX == destX)//didnt change place
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
