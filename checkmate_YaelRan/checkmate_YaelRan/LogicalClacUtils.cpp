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
	if (whosTurn) //white played - black king check
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

bool LogicalClac::isKnightnCheck(const int kingX, const int kingY, const char knight, Piece*** board)
{
	//knightCheck - checks all the 8 possible knight check positions, (and make sure no index out of range occures) 
	if ((kingX < SIDE_SIZE - 2 && kingY > 0 && kingY < SIDE_SIZE - 1	&&	 (board[kingY + 1][kingX + 2]->GetName() == knight || board[kingY - 1][kingX + 2]->GetName() == knight) ||
		kingX >= 2 && kingY > 0 && kingY < SIDE_SIZE - 1				&&	 (board[kingY + 1][kingX - 2]->GetName() == knight || board[kingY - 1][kingX - 2]->GetName() == knight) ||
		kingY < SIDE_SIZE - 2 && kingX > 0 && kingX < SIDE_SIZE - 1		&&	 (board[kingY + 2][kingX + 1]->GetName() == knight || board[kingY + 2][kingX - 1]->GetName() == knight) ||
		kingY >= 2 && kingX > 0 && kingX < SIDE_SIZE - 1				&&	 (board[kingY - 2][kingX + 1]->GetName() == knight || board[kingY - 2][kingX - 1]->GetName() == knight)))
	{
		return true;
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
		if (kingX + i < SIDE_SIZE && kingY + i < SIDE_SIZE && kingY - i >= 0) //right checks
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
		if (kingX - i >= 0 && kingY + i < SIDE_SIZE && kingY - i >= 0) //left checks
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
		if (kingY + i < SIDE_SIZE && kingX + i < SIDE_SIZE && kingX - i >= 0) //up checks
		{
			if (upStright && board[kingY + i][kingX]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				upStright = false;
				if (board[kingY + i][kingX]->GetName() == queen || board[kingY + i][kingX]->GetName() == rook) //stright
				{
					return true;
				}
			}
			if (upDiagLeft && board[kingY + i][kingX - i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				upDiagLeft = false;
				if (board[kingY + i][kingX - i]->GetName() == queen || board[kingY + i][kingX - i]->GetName() == bishop) //diagnle left
				{
					return true;
				}
			}
			if (upDiagRight && board[kingY + i][kingX + i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				upDiagRight = false;
				if (board[kingY + i][kingX + i]->GetName() == queen || board[kingY + i][kingX + i]->GetName() == bishop) //diagnle right
				{
					return true;
				}
			}
			
		}
		if (kingY - i >= 0 && kingX + i < SIDE_SIZE && kingX - i >= 0) //down checks
		{
			if (downStright && board[kingY - i][kingX]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				downStright = false;
				if (board[kingY - i][kingX]->GetName() == queen || board[kingY - i][kingX]->GetName() == rook) //stright
				{
					return true;
				}
			}
			if (downDiagRight && board[kingY - i][kingX + i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				downDiagRight = false;
				if (board[kingY - i][kingX + i]->GetName() == queen || board[kingY - i][kingX + i]->GetName() == bishop) //diagnle right
				{
					return true;
				}
			}
			if (downDiagLeft && board[kingY - i][kingX - i]->GetName() != '#') //checks if not blocked already and not NullPiece)
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
