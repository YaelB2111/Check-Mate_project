#include "Rook.h"

Rook::Rook(char name) : Piece(name)
{
}

Rook::~Rook()
{
}

bool Rook::IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[], int& result, bool whitePlays)
{
	char name = 'R';
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
bool IsLegalForward(const int destY, const int srcX, const int srcY, const Piece* board[])
{
	int i = 0;
	bool legal = true;

	for (i = srcY; i < destY && !legal; i++)
	{
		if (board[srcX][i].GetName() != ' ')
		{
			legal = false;
		}
	}
	return legal;
}bool IsLegalBackward(const int destY, const int srcX, const int srcY, const Piece** board)
{
	int i = 0;
	bool legal = true;
	
	for (i = srcY; i > destY && !legal; i--)
	{
		if (board[srcX][i].GetName() != ' ')
		{
			legal = false;
		}
	}
	return legal;
}

bool IsLegalRight(const int destX, const int srcX, const int srcY, const Piece** board)
{
	int i = 0;
	bool legal = true;

	for (i = srcX; i < destX && !legal; i++)
	{
		if (board[i][srcY].GetName() != ' ')
		{
			legal = false;
		}
	}
	return legal;
}
bool IsLegalLeft(const int destX, const int srcX, const int srcY, const Piece** board)
{
	int i = 0;
	bool legal = true;

	for (i = srcX; i > destX && !legal; i--)
	{
		if (board[i][srcY].GetName() != ' ')
		{
			legal = false;
		}
	}
	return legal;
}