#include "Queen.h"

Queen::Queen(char name) : Piece(name)
{
}

Queen::~Queen()
{
}

bool Queen::IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[], int& result, bool whitePlays)
{
	char name = 'q';
	bool legal = false;
	int boardSize = sizeof(board) / sizeof(board[0]);

	if (whitePlays)
	{
		name = toupper(name); // white is caps (Q)
	}
	if (name != board[srcX][srcY].GetName()) // player with with a piece thats not his
	{
		result = NO_PIECE_SRC;
		return legal;
	}

	if (whitePlays && board[destX][destY].GetName() == toupper(board[destX][destY].GetName())) // for white, dest piece is also white
	{
		result = PIECE_DST;
		return legal;
	}

	else if (!whitePlays && board[destX][destY].GetName() == toupper(board[destX][destY].GetName()))// for black, dest piece is also black
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

	if (abs(destX - srcX) != abs(destY - srcY) || destX != srcX && destY != srcY) // slant should have same x and y change or like rook
	{
		result = INVALID_MOVE;
		return legal;
	}

	if (srcX != destX && destY != srcY) // to move like bishop
	{
		if (srcY > destY && srcX > destX) // for moving down and left
		{
			legal = MoveLeftBot(destX, destY, srcX, srcY, board);
		}
		else if (srcY > destY && srcX < destX)// for moving down and right
		{
			legal = MoveRightBot(destX, destY, srcX, srcY, board);
		}
		else if (srcY < destY && srcX > destX)// for moving up and left
		{
			legal = MoveLeftTop(destX, destY, srcX, srcY, board);
		}
		else// for moving up and right
		{
			legal = MoveRightTop(destX, destY, srcX, srcY, board);
		}


	}
	else // move like rook
	{
		if (srcY > destY)
		{
			legal = IsLegalBackward(destY, srcX, srcY, board); // stright, down
		}
		else if (destY > srcY)
		{
			legal = IsLegalForward(destY, srcX, srcY, board); // stright, up
		}
		else if (srcX > destX)
		{
			legal = IsLegalLeft(destX, srcX, srcY, board); // stright, left
		}
		else
		{
			legal = IsLegalRight(destX, srcX, srcY, board); // stright, right
		}

	}
	if (!legal)
	{
		result = INVALID_MOVE;
		return legal;
	}

	legal = false;

	if (srcY == destY && srcX == destX)// dest = src, no movement
	{
		result = SRC_DST_EQUAL;
		return legal;
	}

	whitePlays = !whitePlays;
	legal = true;
	if (IsSelfCheck(srcX, srcY, board, whitePlays)) // check if move made check on other player
	{
		result = TO_CHECK_MOVE;
		return legal;
	}


	result = VALID_MOVE;
	return legal;
}

bool Queen::IsLegalForward(const int destY, const int srcX, const int srcY, const Piece* board[])
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

bool Queen::IsLegalBackward(const int destY, const int srcX, const int srcY, const Piece** board)
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

bool Queen::IsLegalRight(const int destX, const int srcX, const int srcY, const Piece** board)
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

bool Queen::IsLegalLeft(const int destX, const int srcX, const int srcY, const Piece** board)
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

bool Queen::MoveRightTop(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[]) const
{
	int i = 0, j = 0;
	bool legal = true;

	j = srcX;
	for (i = srcY; i < destY; i++, j++)
	{
		if (board[j][i].GetName() != '#')
		{
			return false;
		}
	}
	return legal;
}

bool Queen::MoveRightBot(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[]) const
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

bool Queen::MoveLeftTop(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[]) const
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

bool Queen::MoveLeftBot(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[]) const
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

