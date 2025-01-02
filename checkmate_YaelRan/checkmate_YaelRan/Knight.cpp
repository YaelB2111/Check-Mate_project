#include "Knight.h"

Knight::Knight(char name) : Piece(name)
{
}

Knight::~Knight()
{
}

bool Knight::IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece* board[], int& result, bool whitePlays)
{
	char name = 'k';
	bool legal = false;
	int boardSize = sizeof(board) / sizeof(board[0]);

	if (whitePlays) // white is caps
	{
		name = toupper(name);
	}

	if (name != board[srcX][srcY].GetName()) // dest is empty or the other team's piece
	{
		result = NO_PIECE_SRC;
		return legal;
	}
	
	if (whitePlays && board[destX][destY].GetName() != tolower(board[destX][destY].GetName())) // if white tries to eats white
	{
		result = PIECE_DST;
		return legal;
	}

	else if (!whitePlays && board[destX][destY].GetName() != toupper(board[destX][destY].GetName()))// if black tries to eats black
	{
		result = PIECE_DST;
		return legal;
	}

	if (IsSelfCheck(srcX, srcY, board, whitePlays)) // self check
	{
		result = SELF_CHECK;
		return legal;
	}

	if (destX >= boardSize || srcX >= boardSize || destY >= boardSize || srcY >= boardSize) // out of board
	{
		result = OUT_OF_BOUND;
		return legal;
	}

	if (!((abs(destX - srcX ) == 1 && abs(destY - srcY) == 2) || (abs(destX - srcX) == 2 && abs(destY - srcY) == 1))) // knight can move 2 to a side and 1 to the other
	{
		result = INVALID_MOVE;
		return legal;
	}


	if (srcY == destY && srcX == destX) // didnt move
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

