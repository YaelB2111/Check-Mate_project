#include "Bishop.h"

Bishop::Bishop(char name):Piece(name)
{
}

Bishop::~Bishop()
{
}

bool Bishop::IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[], int& result, bool whitePlays)
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


	if (srcY > destY && srcX > destX)
	{
		legal = MoveLeftBot(destX, destY, srcX, srcY, board);
	}
	else if (srcY > destY && srcX < destX)
	{
		legal = MoveRightBot(destX, destY, srcX, srcY, board);
	}
	else if (srcY < destY && srcX > destX)
	{
		legal = MoveLeftTop(destX, destY, srcX, srcY, board);
	}
	else
	{
		legal = MoveRightTop(destX, destY, srcX, srcY, board);
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

bool Bishop::MoveRightTop(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[]) const
{
	int i = 0, j = 0;
	bool legal = true;

	j = srcX;
	for (i = srcY; i < destY ; i++ , j ++)
	{
		if (board[j][i].GetName() != '#')
		{
			return false;
		}
	}
	return legal;
}

bool Bishop::MoveRightBot(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[]) const
{
	int i = 0, j = 0;
	bool legal = true;

	j = srcX;
	for (i = srcY; i > destY; i--, j++)
	{
		if (board[j][i].GetName() != '#')
		{
			return false;
		}
	}
	return legal;
}

bool Bishop::MoveLeftTop(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[]) const

{
	int i = 0, j = 0;
	bool legal = true;

	j = srcX;
	for (i = srcY; i < destY; i++, j--)
	{
		if (board[j][i].GetName() != '#')
		{
			return false;
		}
	}
	return legal;
}


bool Bishop::MoveLeftBot(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[]) const
{
	int i = 0, j = 0;
	bool legal = true;

	j = srcX;
	for (i = srcY; i > destY; i--, j--)
	{
		if (board[j][i].GetName() != '#')
		{
			return false;
		}
	}
	return legal;
}