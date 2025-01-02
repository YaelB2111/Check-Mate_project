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
		if (kingY < SIDE_SIZE - 1 && kingX < SIDE_SIZE - 1 && kingX > 0 && board[kingX + 1][kingY - 1]->GetName() == 'P' || board[kingX - 1][kingY - 1]->GetName() == 'P')
		{
			return true;
		}
	}
	else //black played - white king check
	{
		if (kingY < SIDE_SIZE - 1 && kingX < SIDE_SIZE - 1 && kingX > 0 && board[kingX + 1][kingY + 1]->GetName() == 'p' || board[kingX - 1][kingY + 1]->GetName() == 'p')
		{
			return true;
		}
	}
	return false;
}

bool LogicalClac::isKnightnCheck(const int kingX, const int kingY, const char knight, Piece*** board)
{
	//knightCheck - checks all the 8 possible knight check positions, (and make sure no index out of range occures) 
	if ((kingX < SIDE_SIZE - 2 && kingY > 0 && kingY < SIDE_SIZE	&&	 (board[kingX + 2][kingY + 1]->GetName() == knight || board[kingX + 2][kingY - 1]->GetName() == knight) ||
		kingX >= 2 && kingY > 0 && kingY < SIDE_SIZE				&&	 (board[kingX - 2][kingY + 1]->GetName() == knight || board[kingX - 2][kingY - 1]->GetName() == knight) ||
		kingY < SIDE_SIZE - 2 && kingX > 0 && kingX < SIDE_SIZE		&&	 (board[kingX + 1][kingY + 2]->GetName() == knight || board[kingX - 1][kingY + 2]->GetName() == knight) ||
		kingY >= 2 && kingX > 0 && kingX < SIDE_SIZE				&&	 (board[kingX + 1][kingY - 2]->GetName() == knight || board[kingX - 1][kingY - 2]->GetName() == knight)))
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
			if (rightStright && board[kingX + i][kingY]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				rightStright = false;
				if (board[kingX + i][kingY]->GetName() == queen || board[kingX + i][kingY]->GetName() == rook) //stright
				{
					return true;
				}
			}
		}
		if (kingX - i >= 0 && kingY + i < SIDE_SIZE && kingY - i >= 0) //left checks
		{
			if (leftStright && board[kingX - i][kingY]->GetName() != '#')  //checks if not blocked already and not NullPiece
			{
				leftStright = false;
				if (board[kingX - i][kingY]->GetName() == queen || board[kingX - i][kingY]->GetName() == rook) //stright
				{
					return true;
				}
			}
		}
		if (kingY + i < SIDE_SIZE && kingX + i < SIDE_SIZE && kingX - i >= 0) //up checks
		{
			if (upStright && board[kingX][kingY + i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				upStright = false;
				if (board[kingX][kingY + i]->GetName() == queen || board[kingX][kingY + i]->GetName() == rook) //stright
				{
					return true;
				}
			}
			if (upDiagLeft && board[kingX - i][kingY + i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				upDiagLeft = false;
				if (board[kingX - i][kingY + i]->GetName() == queen || board[kingX - i][kingY + i]->GetName() == bishop) //diagnle left
				{
					return true;
				}
			}
			if (upDiagRight && board[kingX + i][kingY + i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				upDiagRight = false;
				if (board[kingX + i][kingY + i]->GetName() == queen || board[kingX + i][kingY + i]->GetName() == bishop) //diagnle right
				{
					return true;
				}
			}
			
		}
		if (kingY - i >= 0 && kingX + i < SIDE_SIZE && kingX - i >= 0) //down checks
		{
			if (downStright && board[kingX][kingY - i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				downStright = false;
				if (board[kingX][kingY - i]->GetName() == queen || board[kingX][kingY - i]->GetName() == rook) //stright
				{
					return true;
				}
			}
			if (downDiagRight && board[kingX + i][kingY - i]->GetName() != '#') //checks if not blocked already and not NullPiece
			{
				downDiagRight = false;
				if (board[kingX + i][kingY - i]->GetName() == queen || board[kingX + i][kingY - i]->GetName() == bishop) //diagnle right
				{
					return true;
				}
			}
			if (downDiagLeft && board[kingX - i][kingY - i]->GetName() != '#') //checks if not blocked already and not NullPiece)
			{
				downDiagLeft = false;
				if (board[kingX - i][kingY - i]->GetName() == queen || board[kingX - i][kingY - i]->GetName() == bishop) //diagnle left
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
	for (i = 0; i < SIDE_SIZE; i++)
	{
		for (j = 0; j < SIDE_SIZE; j++)
		{
			if (board[i][j] == nullptr)
			{
				board[i][j] = new NullPiece();
			}
		}
	}
}
