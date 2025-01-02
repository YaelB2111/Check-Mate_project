#include "Pawn.h"

Pawn::Pawn(char name) :Piece(name)
{
}

Pawn::~Pawn()
{
}

bool Pawn::IsMoveLegal(const int destX, const int destY, const int srcX, const int srcY, const Piece*** board, int& result, bool whitePlays)
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

	if (!(abs(destY - srcY) == 1 && abs(destX - srcX) <= 1)) // pawn can move 1 up and max 1 to side 
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
	if (IsSelfCheck(srcX, srcY, board, whitePlays))
	{
		result = TO_CHECK_MOVE;
		return legal;
	}


	result = VALID_MOVE;
	return legal;

}
