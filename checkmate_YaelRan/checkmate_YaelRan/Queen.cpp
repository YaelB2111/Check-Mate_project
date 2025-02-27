#include "Queen.h"

Queen::Queen(char name) : Piece(name)
{
}

Queen::~Queen()
{
}

bool Queen::IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[], int& result, bool whitePlays, bool move)
{
	char name = 'q';
	bool legal = false;
	int boardSize = SIZE;

	if (whitePlays)
	{
		name = toupper(name); // white is caps (Q)
	}
	if (name != board[srcY][srcX]->GetName()) // player with with a piece thats not his
	{
		result = NO_PIECE_SRC;
		return legal;
	}

	if (board[destY][destX]->GetName() != '#' && whitePlays && board[destY][destX]->GetName() == toupper(board[destY][destX]->GetName())) // for white, dest piece is also white
	{
		result = PIECE_DST;
		return legal;
	}

	else if (board[destY][destX]->GetName() != '#' && !whitePlays && board[destY][destX]->GetName() != toupper(board[destY][destX]->GetName()))// for black, dest piece is also black
	{
		result = PIECE_DST;
		return legal;
	}

	if (destX >= boardSize || srcX >= boardSize || destY >= boardSize || srcY >= boardSize) // dest out of board
	{
		result = OUT_OF_BOUND;
		return legal;
	}

	if (abs(destX - srcX) != abs(destY - srcY) && (destX != srcX && destY != srcY)) // slant should have same x and y change or like rook
	{
		result = INVALID_MOVE;
		return legal;
	}


	//check that there's not piece in the middle of the move
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

	result = VALID_MOVE;
	return legal;
}

bool Queen::IsLegalForward(const int destY, const int srcX, const int srcY, const Piece** board[])
{
	int i = 0;
	bool legal = true;

	for (i = srcY + 1; i < destY && legal; i++)
	{
		if (board[i][srcX]->GetName() != '#')
		{
			legal = false;
		}
	}
	return legal;
}

bool Queen::IsLegalBackward(const int destY, const int srcX, const int srcY, const Piece*** board)
{

	int i = 0;
	bool legal = true;

	for (i = srcY - 1; i > destY && legal; i--)
	{
		if (board[i][srcX]->GetName() != '#')
		{
			legal = false;
		}
	}
	return legal;
}

bool Queen::IsLegalRight(const int destX, const int srcX, const int srcY, const Piece*** board)
{
	int i = 0;
	bool legal = true;

	for (i = srcX + 1; i < destX && legal; i++)
	{
		if (board[srcY][i]->GetName() != '#')
		{
			legal = false;
		}
	}
	return legal;
}

bool Queen::IsLegalLeft(const int destX, const int srcX, const int srcY, const Piece*** board)
{
	int i = 0;
	bool legal = true;

	for (i = srcX - 1 ; i > destX && legal; i--)
	{
		if (board[srcY][i]->GetName() != '#')
		{
			legal = false;
		}
	}
	return legal;
}

bool Queen::MoveRightTop(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[]) const
{
	int i = 0, j = 0;
	bool legal = true;

	j = srcX + 1;
	for (i = srcY + 1; i < destY; i++, j++)
	{
		if (board[i][j]->GetName() != '#')
		{
			return false;
		}
	}
	return legal;
}

bool Queen::MoveRightBot(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[]) const
{
	int i = 0, j = 0;
	bool legal = true;

	j = srcX + 1;
	for (i = srcY - 1; i > destY; i--, j++)
	{
		if (board[i][j]->GetName() != '#')
		{
			return false;
		}
	}
	return legal;
}

bool Queen::MoveLeftTop(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[]) const
{
	int i = 0, j = 0;
	bool legal = true;

	j = srcX - 1;
	for (i = srcY + 1; i < destY; i++, j--)
	{
		if (board[i][j]->GetName() != '#')
		{
			return false;
		}
	}
	return legal;
}

bool Queen::MoveLeftBot(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[]) const
{
	int i = 0, j = 0;
	bool legal = true;

	j = srcX - 1;
	for (i = srcY - 1; i > destY; i--, j--)
	{
		if (board[i][j]->GetName() != '#')
		{
			return false;
		}
	}
	return legal;
}

