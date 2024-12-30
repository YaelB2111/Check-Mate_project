#include "Knight.h"

Knight::Knight(char name) : Piece(name)
{
}

Knight::~Knight()
{
}

bool Knight::IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[], int& result, bool whitePlays)
{
	char name = 'K';
	bool legal = false;
	int boardSize = sizeof(board) / sizeof(board[0]);

	if (whitePlays)
	{
		name = toupper(name);
	}
	if (name != board[srcX][srcY].GetName())
	{
		result = NO_PIECE_SRC;
		return legal;
	}

	if (whitePlays && board[destX][destY].GetName() == tolower(board[destX][destY].GetName()))
	{
		result = PIECE_DST;
		return legal;
	}

	else if (!whitePlays && board[destX][destY].GetName() == toupper(board[destX][destY].GetName()))
	{
		result = PIECE_DST;
		return legal;
	}

	if (IsSelfCheck(srcX, srcY, board, whitePlays))
	{
		result = SELF_CHECK;
		return legal;
	}

	if (destX >= boardSize || srcX >= boardSize || destY >= boardSize || srcY >= boardSize)
	{
		result = OUT_OF_BOUND;
		return legal;
	}

	if (destX != srcX && destY != srcY)
	{
		result = INVALID_MOVE;
		return legal;
	}

	if (!((abs(destX - srcX ) == 1 && abs(destY - srcY) == 2) || (abs(destX - srcX) == 2 && abs(destY - srcY) == 1)))
	{
		result = INVALID_MOVE;
		return legal;
	}


	if (srcY == destY && srcX == destX)
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

