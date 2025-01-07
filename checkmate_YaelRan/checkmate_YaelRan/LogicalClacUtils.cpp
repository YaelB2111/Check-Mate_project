#include "LogicalClacUtils.h"

void LogicalClac::findKingCordinates(int& kingX, int& kingY, const char checkedKing, Piece*** board)
{
	int i = 0, j = 0;
	bool finished = false;
	for (i = 0; i < SIDE_SIZE && !finished; i++) //find the cordinates of the prefered king
	{
		for (j = 0; j < SIDE_SIZE && !finished; j++)
		{
			if (board[i][j]->GetName() == checkedKing)
			{
				kingX = j;
				kingY = i;
				finished = true;
			}
		}
	}
}



bool LogicalClac::isPawnCheck(const int kingX, const int kingY, const bool whosTurn, Piece*** board)
{
	//pawn check
	if (!whosTurn) //white played - black king check
	{
		if (kingY > 0 && kingY < SIDE_SIZE - 1 && kingX < SIDE_SIZE - 1 && kingX > 0 && (board[kingY - 1][kingX + 1]->GetName() == 'P' || board[kingY - 1][kingX - 1]->GetName() == 'P'))
		{
			return true;
		}
	}
	else //black played - white king check
	{
		if (kingY > 0 && kingY < SIDE_SIZE - 1 && kingX < SIDE_SIZE - 1 && kingX > 0 && (board[kingY + 1][kingX + 1]->GetName() == 'p' || board[kingY + 1][kingX - 1]->GetName() == 'p'))
		{
			return true;
		}
	}
	return false;
}

bool LogicalClac::isKingCheck(const int kingX, const int kingY, const char king, Piece*** board)
{
	bool rightCheck = kingX < SIDE_SIZE - 1, leftCheck = kingX > 0, upCheck = kingY < SIDE_SIZE - 1, downCheck = kingY > 0;
	if (upCheck) //up
	{
		if (board[kingY + 1][kingX]->GetName() == king)
		{
			return true;
		}
		if (rightCheck && board[kingY + 1][kingX + 1]->GetName() == king) //up right
		{
			return true;
		}
		if (leftCheck && board[kingY + 1][kingX - 1]->GetName() == king) //up left
		{
			return true;
		}
	}
	if (downCheck) //down
	{
		if (board[kingY - 1][kingX]->GetName() == king)
		{
			return true;
		}
		if (rightCheck && board[kingY - 1][kingX + 1]->GetName() == king) //down right
		{
			return true;
		}
		if (leftCheck && board[kingY - 1][kingX - 1]->GetName() == king) //down left
		{
			return true;
		}
	}
	if (rightCheck && board[kingY][kingX + 1]->GetName() == king) //right
	{
		return true;
	}
	if (leftCheck && board[kingY][kingX - 1]->GetName() == king) //left
	{
		return true;
	}
	return false;
}

bool LogicalClac::isKnightnCheck(const int kingX, const int kingY, const char knight, Piece*** board)
{
	//knightCheck - checks all the 8 possible knight check positions, (and make sure no index out of range occures) 
	if (kingX < SIDE_SIZE - 2) //right
	{
		if (kingY < SIDE_SIZE - 1 && board[kingY + 1][kingX + 2]->GetName() == knight) //right up
		{
			return true;
		}
		if (kingY > 0 && board[kingY - 1][kingX + 2]->GetName() == knight) //right down
		{
			return true;
		}
	}
	if (kingX >= 2) //left
	{
		if (kingY < SIDE_SIZE - 1 && board[kingY + 1][kingX - 2]->GetName() == knight) //left up
		{
			return true;
		}
		if (kingY > 0 && board[kingY - 1][kingX - 2]->GetName() == knight) //left down
		{
			return true;
		}
	}
	if (kingY < SIDE_SIZE - 2) //up
	{
		if (kingX < SIDE_SIZE - 1 && board[kingY + 2][kingX + 1]->GetName() == knight) //up right
		{
			return true;
		}
		if (kingX > 0 && board[kingY + 2][kingX - 1]->GetName() == knight) //up left
		{
			return true;
		}
	}
	if (kingY >= 2) //down
	{
		if (kingX < SIDE_SIZE - 1 && board[kingY - 2][kingX + 1]->GetName() == knight) //down right
		{
			return true;
		}
		if (kingX > 0 && board[kingY - 2][kingX - 1]->GetName() == knight) //down left
		{
			return true;
		}
	}
	return false;
}

bool LogicalClac::isStrightDiagnleCheck(const int kingX, const int kingY, const char queen, const char rook, const char bishop, Piece*** board)
{
	int i = 0;
	bool rightStright = true, leftStright = true, upStright = true, downStright = true,
		upDiagRight = true, upDiagLeft = true, downDiagRight = true, downDiagLeft = true;
	for (i = 1; i < SIDE_SIZE; i++) //quenn, rook & bishop check
	{
		if (kingX + i < SIDE_SIZE) //right checks
		{
			if (rightStright && board[kingY][kingX + i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				rightStright = false;
				if (board[kingY][kingX + i]->GetName() == queen || board[kingY][kingX + i]->GetName() == rook) //stright
				{
					return true;
				}
			}
		}
		if (kingX - i >= 0) //left checks
		{
			if (leftStright && board[kingY][kingX - i]->GetName() != '#')  //checks if not blocked already and not NullPiece
			{
				leftStright = false;
				if (board[kingY][kingX - i]->GetName() == queen || board[kingY][kingX - i]->GetName() == rook) //stright
				{
					return true;
				}
			}
		}
		if (kingY + i < SIDE_SIZE) //up checks
		{
			if (upStright && board[kingY + i][kingX]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				upStright = false;
				if (board[kingY + i][kingX]->GetName() == queen || board[kingY + i][kingX]->GetName() == rook) //stright
				{
					return true;
				}
			}
			if (kingX - i >= 0 && upDiagLeft && board[kingY + i][kingX - i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				upDiagLeft = false;
				if (board[kingY + i][kingX - i]->GetName() == queen || board[kingY + i][kingX - i]->GetName() == bishop) //diagnle left
				{
					return true;
				}
			}
			if (kingX + i < SIDE_SIZE && upDiagRight && board[kingY + i][kingX + i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				upDiagRight = false;
				if (board[kingY + i][kingX + i]->GetName() == queen || board[kingY + i][kingX + i]->GetName() == bishop) //diagnle right
				{
					return true;
				}
			}
			
		}
		if (kingY - i >= 0) //down checks
		{
			if (downStright && board[kingY - i][kingX]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				downStright = false;
				if (board[kingY - i][kingX]->GetName() == queen || board[kingY - i][kingX]->GetName() == rook) //stright
				{
					return true;
				}
			}
			if (kingX + i < SIDE_SIZE && downDiagRight && board[kingY - i][kingX + i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				downDiagRight = false;
				if (board[kingY - i][kingX + i]->GetName() == queen || board[kingY - i][kingX + i]->GetName() == bishop) //diagnle right
				{
					return true;
				}
			}
			if (kingX - i >= 0 && downDiagLeft && board[kingY - i][kingX - i]->GetName() != '#') //checks if not blocked already and not NullPiece)
			{
				downDiagLeft = false;
				if (board[kingY - i][kingX - i]->GetName() == queen || board[kingY - i][kingX - i]->GetName() == bishop) //diagnle left
				{
					return true;
				}
			}
		}
	}
	return false;
}

void LogicalClac::convertMsgToCordinates(string msg, int& srcX, int& srcY, int& dstX, int& dstY)
{
	srcX = int(msg[0])-'a';
	srcY = int(msg[1]) - '1';
	dstX = int(msg[2]) - 'a';
	dstY = int(msg[3]) - '1';
}

void LogicalClac::replaceNullWithNullObj(Piece*** board)
{
	int i = 0, j = 0;
	bool replaced = false;
	for (i = 0; i < SIDE_SIZE && !replaced; i++)
	{
		for (j = 0; j < SIDE_SIZE && !replaced; j++)
		{
			if (board[i][j] == nullptr)
			{
				board[i][j] = new NullPiece();
				replaced = true;
			}
		}
	}
}
