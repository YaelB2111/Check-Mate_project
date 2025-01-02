#include "Bishop.h"

Bishop::Bishop(char name):Piece(name)
{
}

Bishop::~Bishop()
{
}

bool Bishop::IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[], int& result, bool whitePlays)
{
	char name = 'b';
	bool legal = false;
	int boardSize = SIZE;

	if (whitePlays)
	{
		name = toupper(name); // white is caps (B)
	}
	if (name != board[srcX][srcY]->GetName()) // player with with a piece thats not his
	{
		result = NO_PIECE_SRC;
		return legal;
	}

	if (whitePlays && board[destX][destY]->GetName() == toupper(board[destX][destY]->GetName())) // for white, dest piece is also white
	{
		result = PIECE_DST;
		return legal;
	}

	else if (!whitePlays && board[destX][destY]->GetName() != toupper(board[destX][destY]->GetName()))// for black, dest piece is also black
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

	if (abs(destX - srcX) != abs(destY - srcY)) // slant should have same x and y change
	{
		result = INVALID_MOVE;
		return legal;
	}

	//check that there's not piece in the middle of the move
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

bool Bishop::MoveRightTop(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[]) const
{
	int i = 0, j = 0;
	bool legal = true;

	j = srcX;
	for (i = srcY; i < destY ; i++ , j ++)
	{
		if (board[j][i]->GetName() != '#')
		{
			return false;
		}
	}
	return legal;
}

bool Bishop::MoveRightBot(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[]) const
{
	int i = 0, j = 0;
	bool legal = true;

	j = srcX;
	for (i = srcY; i > destY; i--, j++)
	{
		if (board[j][i]->GetName() != '#')
		{
			return false;
		}
	}
	return legal;
}

bool Bishop::MoveLeftTop(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[]) const

{
	int i = 0, j = 0;
	bool legal = true;

	j = srcX;
	for (i = srcY; i < destY; i++, j--)
	{
		if (board[j][i]->GetName() != '#')
		{
			return false;
		}
	}
	return legal;
}


bool Bishop::MoveLeftBot(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[]) const
{
	int i = 0, j = 0;
	bool legal = true;

	j = srcX;
	for (i = srcY; i > destY; i--, j--)
	{
		if (board[j][i]->GetName() != '#')
		{
			return false;
		}
	}
	return legal;
}