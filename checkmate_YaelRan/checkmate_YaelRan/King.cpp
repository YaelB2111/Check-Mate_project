#include "King.h"

King::King(char name) : Piece (name), _moved(false)
{
}

King::~King()
{
}

bool King::IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece** board[], int& result, bool whitePlays, bool move)
{
	char name = 'k';
	bool legal = false;
	int boardSize = SIZE;

	if (whitePlays) // for white K
	{
		name = toupper(name);
	}

	if (name != board[srcY][srcX]->GetName()) // no piece in source or not right team
	{
		result = NO_PIECE_SRC;
		return legal;
	}

	if (whitePlays && board[destY][destX]->GetName() != tolower(board[destY][destX]->GetName()))// if white eats white
	{
		result = PIECE_DST;
		return legal;
	}

	else if (!whitePlays && board[destY][destX]->GetName() != toupper(board[destY][destX]->GetName())) // if black eats black
	{
		result = PIECE_DST;
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

	legal = true;


	result = VALID_MOVE;
	return legal;
}

void King::SetMoved()
{
	this->_moved = true;
}

bool King::GetMoved()
{
	return this->_moved;
}
