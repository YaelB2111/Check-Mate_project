#include "Pawn.h"

Pawn::Pawn(char name) :Piece(name)
{
	this->_moved = false;
}

Pawn::~Pawn()
{
}

void Pawn::SetMoved()
{
	this->_moved = true;
}

bool Pawn::IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece*** board, int& result, bool whitePlays, bool move)
{
	char name = 'p';
	bool legal = false;
	int boardSize = SIZE;

	if (whitePlays) // white is caps
	{
		name = toupper(name);
	}

	if (name != board[srcY][srcX]->GetName()) // dest is empty or the other team's piece
	{
		result = NO_PIECE_SRC;
		return legal;
	}

	if (whitePlays && board[destY][destX]->GetName() != tolower(board[destY][destX]->GetName())) // if white tries to eats white
	{
		result = PIECE_DST;
		return legal;
	}

	else if (!whitePlays && board[destY][destX]->GetName() != toupper(board[destY][destX]->GetName()))// if black tries to eats black
	{
		result = PIECE_DST;
		return legal;
	}

	if (move && IsSelfCheck(srcX, srcY, board, whitePlays)) // self check
	{
		result = SELF_CHECK;
		return legal;
	}

	if (destX >= boardSize || srcX >= boardSize || destY >= boardSize || srcY >= boardSize) // out of board
	{
		result = OUT_OF_BOUND;
		return legal;
	}

	if (abs(destY - srcY) == 2 && srcX == destX) // for first move
	{
		if (board[destY][destX]->GetName() != '#' || this->_moved)//it cant eat straight and its only for first move
		{
			result = INVALID_MOVE;
			return legal;
		}
	}
	else if (!(abs(destY - srcY) == 1 && abs(destX - srcX) <= 1)) // pawn can move 1 up and max 1 to side 
	{
		result = INVALID_MOVE;
		return legal;
	}

	//try to eat forward
	if (destX - srcX == 0 && board[destY][destX]->GetName() != '#')
	{
		result = INVALID_MOVE;
		return legal;
	}

	//try to move with x change
	if (destX - srcX != 0 && board[destY][destX]->GetName() == '#')
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
	if (move && IsSelfCheck(srcX, srcY, board, whitePlays))
	{
		result = TO_CHECK_MOVE;
		return legal;
	}


	result = VALID_MOVE;
	return legal;

}
