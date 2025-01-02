#include "Piece.h"

Piece::Piece(char name)
{
	this->_name = name;
}

Piece::~Piece()
{
	this->_name = ' ';
}

char Piece::GetName() const
{
	return this->_name;
}

void Piece::MovePlace(int destX, int destY, int srcX, int srcY, Piece** board[])
{
	Piece* temp = board[destY][destX];
	if (board[destY][destX]->GetName() != '#')
	{
		Eat(destX, destY, srcX, srcY, board);
	}
	else
	{
		board[destY][destX] = board[srcY][srcX];
		board[srcY][srcX] = temp;
	}
}

bool Piece::IsSelfCheck(const int srcX, const int srcY, const Piece** board[], const bool whitePlays)
{
	int kingX = 0, kingY = 0;

	int i = 0, rows = SIZE, j = 0 , cols = SIZE, result = 0;
	bool selfCheck = false;
	char lettterToFind = 'K';
	
	if (whitePlays)
	{
		lettterToFind = 'k'; // to lower
	}

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (board[j][i]->_name == lettterToFind)
			{
				kingX = j;
				kingY = i;
			}
		}
	}

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols && !selfCheck; j++)
		{
			if (IsMoveLegal(j, i, kingX, kingY, board, result, whitePlays) == true)
			{
				selfCheck = true;
			}
		}
	}
	return selfCheck;
}

void Piece::Eat(int destX, int destY, int srcX, int srcY, Piece** board[])
{
	board[destX][destY] = board[srcX][srcY];
	//board[srcX][srcY] = new NullPiece();
}


