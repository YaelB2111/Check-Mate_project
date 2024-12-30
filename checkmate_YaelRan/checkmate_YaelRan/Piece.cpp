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

void Piece::MovePlace(int destX, int destY, int srcX, int srcY, Piece* board[])
{
	if (board[destX][destY].GetName() != ' ')
	{
		Eat(destX, destY, srcX, srcY, board);
	}
	else
	{
		board[srcX][srcY]._name = ' ';
		// add null piece
	}
}

bool Piece::IsSelfCheck(const int srcX, const int srcY, const Piece* board[], const bool whitePlays)
{
	int kingX = 0, kingY = 0;

	int i = 0, rows = sizeof(board) / sizeof(board[0]), j = 0 , cols = sizeof(board[0]) / sizeof(board[0][0]), result = 0;
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
			if (board[j][i]._name == lettterToFind)
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

void Piece::Eat(int destX, int destY, int srcX, int srcY, Piece* board[])
{
	board[destX][destY] = board[srcX][srcY];
	board[srcX][srcY]._name = ' ';
	// add null piece
}


